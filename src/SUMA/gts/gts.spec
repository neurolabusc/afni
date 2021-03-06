Summary: GNU Triangulated Surface Library (GTS)
Name: gts
%define version 0.7.4
%define release 0
%define mybuildroot /var/tmp/%{name}-build
Version: %{version}
Release: %{release}
URL: http://gfs.sf.net
License: GPL
Source: gts-%{version}.tar.gz
Group: Libraries/Research
BuildRoot: %{mybuildroot}

%description
GTS stands for the GNU Triangulated Surface Library. It is an Open
Source Free Software Library intended to provide a set of useful
functions to deal with 3D surfaces meshed with interconnected
triangles.

A brief summary of its main features:

  Simple object-oriented structure giving easy access to topological properties.
  2D dynamic Delaunay and constrained Delaunay triangulations. 
  Robust geometric predicates (orientation, in circle) using fast adaptive floating point arithmetic (adapted from the fine work of Jonathan R. Shewchuk).
  Robust set operations on surfaces (union, intersection, difference). 
  Surface refinement and coarsening (multiresolution models). 
  Dynamic view-independent continuous level-of-detail. 
  Preliminary support for view-dependent level-of-detail. 
  Bounding-boxes trees and Kd-trees for efficient point location and collision/intersection detection.
  Graph operations: traversal, graph partitioning. 
  Metric operations (area, volume, curvature ...). 
  Triangle strips generation for fast rendering. 

%prep
%setup -q  -n gts-%{version}

%build
CFLAGS="$RPM_OPT_FLAGS"
./configure --prefix=%{_prefix} \
    --bindir=%{_bindir} --mandir=%{_mandir} \
    --localstatedir=%{_localstatedir} --libdir=%{_libdir} \
    --datadir=%{_datadir} --includedir=%{_includedir} \
    --sysconfdir=%{_sysconfdir}
make

%install
rm -rf $RPM_BUILD_ROOT

make prefix=$RPM_BUILD_ROOT%{_prefix} bindir=$RPM_BUILD_ROOT%{_bindir} \
    mandir=$RPM_BUILD_ROOT%{_mandir} libdir=$RPM_BUILD_ROOT%{_libdir} \
    localstatedir=$RPM_BUILD_ROOT%{_localstatedir} \
    datadir=$RPM_BUILD_ROOT%{_datadir} \
    includedir=$RPM_BUILD_ROOT%{_includedir} \
    sysconfdir=$RPM_BUILD_ROOT%{_sysconfdir} install

%clean
rm -rf $RPM_BUILD_ROOT

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%doc {NEWS,ChangeLog,INSTALL,README,AUTHORS,THANKS}
/usr/bin
/usr/lib
/usr/include
/usr/share/aclocal/gts.m4

%changelog
* Thu Oct 21 2004 Tim Fenn <fenn@stanford.edu>
- Fix lack of source declaration, dual license problems

* Mon Apr 26 2004 Stephane Popinet <popinet@users.sf.net>
- Initial build.
