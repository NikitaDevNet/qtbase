/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qfontjpcodec_p.h"

#include "qjpunicode_p.h"

QT_BEGIN_NAMESPACE

#ifndef QT_NO_BIG_CODECS

#ifdef Q_OS_UNIX
// JIS X 0201

QFontJis0201Codec::QFontJis0201Codec()
{
}

QByteArray QFontJis0201Codec::_name()
{
    return "jisx0201*-0";
}

int QFontJis0201Codec::_mibEnum()
{
    return 15;
}

QByteArray QFontJis0201Codec::convertFromUnicode(const QChar *uc, int len,  ConverterState *) const
{
    QByteArray rstring;
    rstring.resize(len);
    uchar *rdata = (uchar *) rstring.data();
    const QChar *sdata = uc;
    int i = 0;
    for (; i < len; ++i, ++sdata, ++rdata) {
        if (sdata->unicode() < 0x80) {
            *rdata = (uchar) sdata->unicode();
        } else if (sdata->unicode() >= 0xff61 && sdata->unicode() <= 0xff9f) {
            *rdata = (uchar) (sdata->unicode() - 0xff61 + 0xa1);
        } else {
            *rdata = 0;
        }
    }
    return rstring;
}

QString QFontJis0201Codec::convertToUnicode(const char *, int,  ConverterState *) const
{
    return QString();
}

// JIS X 0208

QFontJis0208Codec::QFontJis0208Codec()
{
    convJP = QJpUnicodeConv::newConverter(QJpUnicodeConv::Default);
}


QFontJis0208Codec::~QFontJis0208Codec()
{
    delete convJP;
    convJP = 0;
}


QByteArray QFontJis0208Codec::_name()
{
    return "jisx0208*-0";
}


int QFontJis0208Codec::_mibEnum()
{
    return 63;
}


QString QFontJis0208Codec::convertToUnicode(const char* /*chars*/, int /*len*/, ConverterState *) const
{
    return QString();
}

QByteArray QFontJis0208Codec::convertFromUnicode(const QChar *uc, int len, ConverterState *) const
{
    QByteArray result;
    result.resize(len * 2);
    uchar *rdata = (uchar *) result.data();
    const QChar *ucp = uc;

    for (int i = 0; i < len; i++) {
        QChar ch(*ucp++);
        ch = convJP->unicodeToJisx0208(ch.unicode());

        if (!ch.isNull()) {
            *rdata++ = ch.row();
            *rdata++ = ch.cell();
        } else {
            *rdata++ = 0;
            *rdata++ = 0;
        }
    }
    return result;
}

#endif

#endif // QT_NO_BIG_CODECS

QT_END_NAMESPACE
