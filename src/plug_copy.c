#include "afni.h"

#ifndef ALLOW_PLUGINS
#  error "Plugins not properly set up -- see machdep.h"
#endif

/***********************************************************************
  Simple plugin to copy a dataset and make a new one.
************************************************************************/

char * COPY_main( PLUGIN_interface * ) ;

static char helpstring[] =
   " Purpose: Creating a copy of a dataset.\n"
   " Inputs:\n"
   " Dataset = A dataset in the current session that exists in memory\n"
   "             (not warp-on-demand).\n"
   " Prefix  = Filename prefix to be used for the output dataset.\n"
   " Fill    = How to fill voxel data in new dataset:\n"
   "             Data [All] = copy all sub-bricks from input\n"
   "             Zero [All] = fill all sub-bricks with zero\n"
   "             Zero [One] = make new dataset have only 1 sub-brick,\n"
   "                          and fill with zero -- this is useful for\n"
   "                          creating mask datasets using the\n"
   "                          'Draw Dataset' plugin.\n"
   " Type    = Lets you change the 'type' of the output dataset, for\n"
   "             example from anat to func.\n"
   "Author -- RWCox"
;

#define NFILL 3
static char * fill_options[NFILL] = { "Data [All]" , "Zero [All]" , "Zero [One]" } ;

/***********************************************************************
   Set up the interface to the user
************************************************************************/

PLUGIN_interface * PLUGIN_init( int ncall )
{
   PLUGIN_interface * plint ;

   if( ncall > 0 ) return NULL ;  /* only one interface */

   /*-- set titles and call point --*/

   plint = PLUTO_new_interface( "Dataset Copy" , "Make a Copy of a Dataset" , helpstring ,
                                 PLUGIN_CALL_VIA_MENU , COPY_main  ) ;

   PLUTO_add_hint( plint , "Make a Copy of a Dataset" ) ;

   PLUTO_set_sequence( plint , "A:newdset:copy" ) ;

   /*-- first line of input: Dataset --*/

   PLUTO_add_option( plint , "Input" , "Input" , TRUE ) ;
   PLUTO_add_dataset(plint , "Dataset" ,
                                    ANAT_ALL_MASK , FUNC_ALL_MASK ,
                                    DIMEN_ALL_MASK | BRICK_ALLTYPE_MASK ) ;

   /*-- second line of input: Prefix for output dataset --*/

   PLUTO_add_option( plint , "Output" , "Output" , TRUE ) ;
   PLUTO_add_string( plint , "Prefix" , 0,NULL , 19 ) ;

   /*-- third line of input: Fill option --*/

   PLUTO_add_option( plint , "Data Fill" , "Data Fill" , FALSE ) ;
   PLUTO_add_string( plint , "Method" ,  NFILL,fill_options , 0 ) ;

   /*-- fourth line of input: Type option --*/

   PLUTO_add_option( plint , "Dataset" , "Dataset" , FALSE ) ;
   PLUTO_add_string( plint , "Type" , NUM_DSET_TYPES,DSET_prefixstr , 0 ) ;

   return plint ;
}

/***************************************************************************
  Main routine for this plugin (will be called from AFNI).
****************************************************************************/

char * COPY_main( PLUGIN_interface * plint )
{
   char * tag , * new_prefix , * cpt ;
   MCW_idcode * idc ;
   THD_3dim_dataset * dset , * new_dset ;
   int ival , zfill=0 , ftyp=-1 , dtyp=-1 ;

   /*--------------------------------------------------------------------*/
   /*----- Check inputs from AFNI to see if they are reasonable-ish -----*/

   if( plint == NULL )
      return "**********************\n"
             "COPY_main:  NULL input\n"
             "**********************"  ;

   PLUTO_next_option(plint) ;
   idc  = PLUTO_get_idcode(plint) ;
   dset = PLUTO_find_dset(idc) ;
   if( dset == NULL )
      return "*****************************\n"
             "COPY_main:  bad input dataset\n"
             "*****************************"  ;

   dtyp = dset->type ;

   PLUTO_next_option(plint) ;
   new_prefix = PLUTO_get_string(plint) ;
   if( ! PLUTO_prefix_ok(new_prefix) )
      return "**********************\n"
             "COPY_main:  bad prefix\n"
             "**********************"  ;

   tag = PLUTO_get_optiontag(plint) ;
   while( tag != NULL ){

      if( strcmp(tag,"Data Fill") == 0 ){
         cpt   = PLUTO_get_string(plint) ;
         if( cpt != NULL )
            zfill = PLUTO_string_index( cpt , NFILL , fill_options ) ;
      }

      else if( strcmp(tag,"Dataset") == 0 ){
         cpt  = PLUTO_get_string(plint) ;
         ftyp = PLUTO_string_index( cpt , NUM_DSET_TYPES,DSET_prefixstr ) ;
         if( ftyp >= 0 ){
            if( ftyp <= LAST_FUNC_TYPE ){
               dtyp = HEAD_FUNC_TYPE ;
            } else {
               ftyp -= (LAST_FUNC_TYPE+1) ;  /* 14 Jul 1998 */
               dtyp  = HEAD_ANAT_TYPE ;
            }
         }
      }

      tag = PLUTO_get_optiontag(plint) ;
   }

   /*------------------------------------------------------*/
   /*---------- At this point, the inputs are OK ----------*/

   /*-- make a new dataset --*/

   if( zfill <= 1 ){
      new_dset = PLUTO_copy_dset( dset , new_prefix ) ;
   } else {
      new_dset = EDIT_empty_copy( dset ) ;

      if( ISFUNCTYPE(dtyp) ) ftyp = FUNC_FIM_TYPE ;  /* 14 Jul 1998 */
   }

   if( new_dset == NULL )
      return  "****************************************\n"
              "COPY_main:  failed to copy input dataset\n"
              "****************************************"  ;

   DSET_unload( dset ) ;  /* unload old one from memory */

   /*--- modify dataset, if desired ---*/

   if( ftyp >= 0 ) EDIT_dset_items( new_dset ,
                                       ADN_type      , dtyp ,
                                       ADN_func_type , ftyp ,
                                    ADN_none ) ;

   /* if 'Zero [One]', make a brick */

   if( zfill == 2 ){
      int ityp , nbytes ;
      void * new_brick ;

      EDIT_dset_items( new_dset ,
                          ADN_prefix , new_prefix ,
                          ADN_label1 , new_prefix ,
                          ADN_nvals  , 1 ,
                          ADN_ntt    , 0 ,
                       ADN_none ) ;

      ityp      = DSET_BRICK_TYPE(new_dset,0) ;
      nbytes    = DSET_BRICK_BYTES(new_dset,0) ;
      new_brick = malloc( nbytes ) ;
      EDIT_substitute_brick( new_dset , 0 , ityp , new_brick ) ;
   }

   if( zfill ){
      int nvals = DSET_NVALS(new_dset) , ival , nbytes ;
      void * bp ;

      for( ival=0 ; ival < nvals ; ival++ ){
         nbytes = DSET_BRICK_BYTES(new_dset,ival) ;  /* how much data */
         bp     = DSET_BRICK_ARRAY(new_dset,ival) ;  /* brick pointer */
         EDIT_BRICK_FACTOR(new_dset,ival,0.0) ;      /* brick factor  */
         memset( bp , 0 , nbytes ) ;
      }
   }

   ival = PLUTO_add_dset( plint , new_dset , DSET_ACTION_MAKE_CURRENT ) ;

   if( ival ){
      THD_delete_3dim_dataset( new_dset , False ) ;
      return "**********************************************\n"
             "COPY_main:  failure to add new dataset to AFNI\n"
             "**********************************************" ;
   }

   /*-- done successfully!!! --*/

   return NULL ;
}
