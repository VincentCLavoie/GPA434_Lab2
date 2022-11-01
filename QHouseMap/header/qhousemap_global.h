#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(QHOUSEMAP_LIB)
#  define QHOUSEMAP_EXPORT Q_DECL_EXPORT
# else
#  define QHOUSEMAP_EXPORT Q_DECL_IMPORT
# endif
#else
# define QHOUSEMAP_EXPORT
#endif
