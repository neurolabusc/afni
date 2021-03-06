#ifndef SUMA_SURFACE_IO_INCLUDED
#define SUMA_SURFACE_IO_INCLUDED

#define SUMA_FS_ANNOT_TAG_COLORTABLE   1
#define SUMA_FS_STRLEN 50

typedef struct {
   int i;
   int r;
   int g;
   int b;
   int flag;
   char name[SUMA_FS_STRLEN];
} SUMA_FS_COLORTABLE_ENTRY;

typedef struct {
   char *fname;
   int nbins;
   SUMA_FS_COLORTABLE_ENTRY *bins;
   SUMA_COLOR_MAP_HASH_DATUM *chd;
} SUMA_FS_COLORTABLE;

typedef struct {
   int N_Vert;
   int N_Vert_alloc;
   float *Vert;

   int N_Face;
   int N_Face_alloc;
   int *Face;

   int N_Point;
   int N_Point_alloc;
   int *Point;
} SUMA_OBJ_STRUCT;
void SUMA_Show_OBJ(SUMA_OBJ_STRUCT *obj, char *Header, int level, FILE *out);
char *SUMA_OBJ_Info(SUMA_OBJ_STRUCT *obj, char *Header, int level); 
SUMA_Boolean SUMA_OBJ_Read_SO(char *fname, SUMA_SurfaceObject *SO, 
                              SUMA_SphereDO **sphdo);
SUMA_SurfaceObject *SUMA_OBJ_2_SO(SUMA_OBJ_STRUCT *obj);
SUMA_OBJ_STRUCT *SUMA_OBJ_Read(char *fname);
SUMA_OBJ_STRUCT *SUMA_Free_OBJ(SUMA_OBJ_STRUCT *obj);

SUMA_SurfaceObject *SUMA_Load_Surface_Object_Wrapper ( 
                        char *if_name, char *if_name2, char *vp_name, 
                        SUMA_SO_File_Type SO_FT, SUMA_SO_File_Format SO_FF, 
                        char *sv_name, int debug);
char *SUMA_RemoveSurfNameExtension (char*Name, SUMA_SO_File_Type oType);
void *SUMA_Prefix2SurfaceName (char *prefix, char *path, char *vp_name, SUMA_SO_File_Type oType, SUMA_Boolean *exists);
void * SUMA_2Prefix2SurfaceName (char *namecoord, char *nametopo, char *path, char *vp_name, SUMA_SO_File_Type oType, SUMA_Boolean *exists);
SUMA_Boolean SUMA_SureFit_Read_Coord (char * f_name, SUMA_SureFit_struct *SF);
SUMA_Boolean SUMA_SureFit_Read_Topo (char * f_name, SUMA_SureFit_struct *SF);
void SUMA_Show_SureFit (SUMA_SureFit_struct *SF, FILE *Out);
SUMA_Boolean SUMA_Free_SureFit (SUMA_SureFit_struct *SF);
SUMA_Boolean SUMA_FreeSurfer_Read (char * f_name, SUMA_FreeSurfer_struct *FS);
SUMA_Boolean SUMA_FreeSurfer_Read_eng (char * f_name, SUMA_FreeSurfer_struct *FS, int debug);
SUMA_Boolean SUMA_FreeSurfer_ReadBin_eng (char * f_name, SUMA_FreeSurfer_struct *FS, int debug);
SUMA_Boolean SUMA_Free_FreeSurfer (SUMA_FreeSurfer_struct *FS);
void SUMA_Show_FreeSurfer (SUMA_FreeSurfer_struct *FS, FILE *Out);
SUMA_Boolean SUMA_Ply_Read (char * f_name, SUMA_SurfaceObject *SO); 
SUMA_Boolean SUMA_Ply_Write (char * f_name, SUMA_SurfaceObject *SO); 
SUMA_Boolean SUMA_STL_Read (char * f_name, SUMA_SurfaceObject *SO); 
SUMA_Boolean SUMA_STL_Write (char * f_name, SUMA_SurfaceObject *SO); 
SUMA_Boolean SUMA_Mnc_Read (char * f_name, SUMA_SurfaceObject *SO); 
SUMA_Boolean SUMA_Mnc_Write (char * f_name, SUMA_SurfaceObject *SO); 
SUMA_Boolean SUMA_VEC_Write (SUMA_SFname *Fname, SUMA_SurfaceObject *SO);
SUMA_Boolean SUMA_VEC_Read(SUMA_SFname *Fname, SUMA_SurfaceObject *SO);
SUMA_Boolean SUMA_FS_Write (char *fileNm, SUMA_SurfaceObject *SO, char *firstLine);
SUMA_Boolean SUMA_SureFit_Write (SUMA_SFname *Fname, SUMA_SurfaceObject *SO);
SUMA_Boolean SUMA_GIFTI_Write (char *fileNm, SUMA_SurfaceObject *SO, 
                               SUMA_SO_File_Format forceencode);
SUMA_Boolean SUMA_BYU_Write (char *fileNm, SUMA_SurfaceObject *SO, int base1);
void SUMA_SaveDrawnROI (char *filename, void *data);
void SUMA_SaveXformOpts (char *filename, void *data);
SUMA_Boolean SUMA_SaveDrawnROI_1D (char *filename, SUMA_SurfaceObject *SO, SUMA_DRAWN_ROI *DrawnROI, int SaveWhat); 
SUMA_Boolean SUMA_SaveDrawnROINIML (char *filename, SUMA_SurfaceObject *SO, SUMA_DRAWN_ROI *DrawnROI, int SaveWhat, int Format); 
SUMA_1D_DRAWN_ROI * SUMA_Free_1DDrawROI (SUMA_1D_DRAWN_ROI *ROI1D);
SUMA_Boolean SUMA_Write_DrawnROI_1D (SUMA_DRAWN_ROI **ROIv, int N_ROI, char *filename); 
SUMA_1D_DRAWN_ROI * SUMA_DrawnROI_to_1DDrawROI (SUMA_DRAWN_ROI *ROI);
SUMA_DRAWN_ROI ** SUMA_OpenDrawnROI_NIML (char *filename, int *N_ROI,
                              SUMA_Boolean ForDisplay, SUMA_SurfaceViewer *sv);
SUMA_DRAWN_ROI ** SUMA_OpenDrawnROI_1D(char *filename, char *Parent_idcode_str, 
                                       int *N_ROI, SUMA_Boolean ForDisplay);
SUMA_DRAWN_ROI **SUMA_MultiColumnsToDrawnROI( 
         int N_Nodes, 
         void *ind, SUMA_VARTYPE ind_type,
         void *col0, SUMA_VARTYPE col0_type,
         void *col1, SUMA_VARTYPE col1_type,
         void *col2, SUMA_VARTYPE col2_type,
         void *col3, SUMA_VARTYPE col3_type,
         SUMA_COLOR_MAP *cmap,
         int edges_only, 
         char *name, char *Parent_idcode_str,
         int *N_ROI, SUMA_Boolean ForDisplay,
         SUMA_Boolean kkk);
void SUMA_OpenDrawnROI (char *filename, void *data);
SUMA_DSET *SUMA_ROIv2Grpdataset (SUMA_DRAWN_ROI** ROIv, int N_ROIv, 
                                 char *Parent_idcode_str, int Pad_to, 
                                 int Pad_val, SUMA_COLOR_MAP **cm) ;
SUMA_DSET *SUMA_ROIv2MultiDset (SUMA_DRAWN_ROI** ROIv, int N_ROIv, 
                                 char *Parent_idcode_str, int Pad_to, 
                                 int Pad_val, SUMA_COLOR_MAP **cm) ;
NI_element *SUMA_ROIv2dataset (SUMA_DRAWN_ROI** ROIv, int N_ROIv, char *Parent_idcode_str, int pad_to, int pad_val);
DList *SUMA_ROIv2NodeLists (SUMA_DRAWN_ROI** ROIv, int N_ROIv, int purgedups) ; 
void SUMA_SaveSOascii (char *filename, void *data);
float * SUMA_readFScurv (char *f_name, int *nrows, int *ncols, SUMA_Boolean rowmajor, SUMA_Boolean SkipCoords);
SUMA_Boolean SUMA_BYU_Read(char *f_name, SUMA_SurfaceObject *SO, int debug, byte hide_negcols); 
SUMA_Boolean SUMA_BrainVoyager_Read(char *f_name, SUMA_SurfaceObject *SO, int debug, byte hide_negcols); 
SUMA_Boolean SUMA_FreeSurfer_WritePatch (char *fileNm, SUMA_SurfaceObject *SO, char *firstLine, SUMA_SurfaceObject *SOparent);
SUMA_FORM_AFNI_DSET_STRUCT *SUMA_New_FormAfniDset_Opt(void);
SUMA_FORM_AFNI_DSET_STRUCT *SUMA_Free_FormAfniDset_Opt(SUMA_FORM_AFNI_DSET_STRUCT *Opt);
THD_3dim_dataset *SUMA_FormAfnidset (float *NodeList, float *vals, int N_vals, SUMA_FORM_AFNI_DSET_STRUCT *Opt);
NI_group *SUMA_SO2nimlSO(SUMA_SurfaceObject *SO, char *optlist, int nlee) ;
SUMA_SurfaceObject *SUMA_nimlSO2SO(NI_group *ngr); 
SUMA_OPEN_DX_STRUCT ** SUMA_Free_OpenDX_StructVec(SUMA_OPEN_DX_STRUCT **dxv, int nobj);
SUMA_Boolean SUMA_OpenDX_Write(char *fname, SUMA_SurfaceObject *SO);
SUMA_Boolean SUMA_OpenDx_Object_Attr(char *op, int nchar, SUMA_OPEN_DX_STRUCT *dx);
SUMA_Boolean SUMA_OpenDx_Object_Components(char *op, int nchar, SUMA_OPEN_DX_STRUCT *dx);
SUMA_OPEN_DX_STRUCT *SUMA_Find_OpenDX_Object_Name(SUMA_OPEN_DX_STRUCT **dxv, int iop, char *nm, int *nf);
SUMA_OPEN_DX_STRUCT *SUMA_Find_OpenDX_Object_Class(SUMA_OPEN_DX_STRUCT **dxv, int iop, char *nm, int *nf);
SUMA_Boolean SUMA_OpenDX_Read_SO(char *fname, SUMA_SurfaceObject *SO);
char * SUMA_OpenDX_Read_CruiseVolHead(char *fname, THD_3dim_dataset *dset, int loaddata);
SUMA_Boolean SUMA_readFSannot (char *f_name, 
                               char *f_ROI, char *f_cmap, char *f_col, 
                               int Showct, char *ctfile,
                               int lbl1, int lbl2,
                               SUMA_DSET **dset);
SUMA_COLOR_MAP *SUMA_FScolutToColorMap(char *fscolutname, 
                                       int lbl1, int lbl2, int show,int idISi); 
SUMA_COLOR_MAP *SUMA_FScolutToColorMap_eng(SUMA_FS_COLORTABLE *ct, 
                                       int lbl1, int lbl2, int show,int idISi); 
SUMA_Boolean SUMA_isnimlSO(NI_group *ngr);
void SUMA_free_ROI_Extract(void *dd);
SUMA_Boolean SUMA_MNI_OBJ_Write(char * f_name_in, SUMA_SurfaceObject *SO);
SUMA_Boolean SUMA_MNI_OBJ_Read(char * f_name, SUMA_SurfaceObject *SO);
SUMA_Boolean SUMA_GIFTI_Read(char *f_name, SUMA_SurfaceObject *SO,
                             int debug);
void set_GIFTI_RAI_warn(int v);
SUMA_Boolean SUMA_GetSOCoordXform(SUMA_SurfaceObject *SO, double xform[4][4]);                          
                             

typedef struct {
   int label;
   char *name;
   int N_vals;
   int N_alloc;
   int *vals;
} SUMA_ROI_EXTRACT;

#endif
