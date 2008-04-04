Summary: Z39.50 Programs
Name: yaz
Version: 2.1.28
Release: 1
Requires: libxslt openssl readline libyaz = %{version}
License: YAZ License
Group: Other
Vendor: Index Data ApS <info@indexdata.dk>
Source: yaz-%{version}.tar.gz
BuildRoot: %{_tmppath}/%{name}-%{version}-root
BuildRequires: libxml2-devel libxslt-devel tcp_wrappers openssl-devel readline-devel
Packager: Adam Dickmeiss <adam@indexdata.dk>
URL: http://www.indexdata.dk/yaz/

%description
This package contains both a test-server and clients (normal & ssl)
for the ANSI/NISO Z39.50 protocol for Information Retrieval.

%package -n lib%{name}
Summary: Z39.50 Library
Group: Libraries
Requires: libxslt openssl

%description -n lib%{name}
YAZ is a library for the ANSI/NISO Z39.50 protocol for Information
Retrieval.

%package -n lib%{name}-devel
Summary: Z39.50 Library - development package
Group: Development/Libraries
Requires: libyaz = %{version} libxml2-devel libxslt-devel

%description -n lib%{name}-devel
Development libraries and includes for the libyaz package.

%prep
%setup

%build

CFLAGS="$RPM_OPT_FLAGS" \
 ./configure --prefix=/usr --enable-shared --enable-tcpd --with-xslt --with-openssl
make CFLAGS="$RPM_OPT_FLAGS"

%install
rm -fr ${RPM_BUILD_ROOT}
make prefix=${RPM_BUILD_ROOT}/usr mandir=${RPM_BUILD_ROOT}/usr/share/man install

%clean
rm -fr ${RPM_BUILD_ROOT}

%files
%defattr(-,root,root)
%doc README LICENSE NEWS TODO
/usr/bin/yaz-client
/usr/bin/yaz-ztest
/usr/bin/zoomsh*
/usr/bin/yaz-marcdump
/usr/bin/yaz-iconv
/usr/share/man/man1/yaz-client.*
/usr/share/man/man8/yaz-ztest.*
/usr/share/man/man1/zoomsh.*
/usr/share/man/man1/yaz-marcdump.*
/usr/share/man/man1/yaz-iconv.*
/usr/share/man/man7/yaz-log.*

%files -n lib%{name}
/usr/lib/*.so.*

%files -n lib%{name}-devel
/usr/bin/yaz-config
/usr/bin/yaz-asncomp
/usr/include/yaz
/usr/lib/*.so
/usr/lib/*.a
/usr/lib/*.la
/usr/share/aclocal/yaz.m4
/usr/share/man/man1/yaz-asncomp.*
/usr/share/man/man7/yaz.*
/usr/share/man/man8/yaz-config.*
/usr/share/doc/yaz
/usr/share/yaz

