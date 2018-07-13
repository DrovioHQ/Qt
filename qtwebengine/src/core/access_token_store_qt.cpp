/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtWebEngine module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "access_token_store_qt.h"

#include "base/bind.h"
#include "base/message_loop/message_loop.h"
#include "base/strings/utf_string_conversions.h"
#include "content/public/browser/browser_thread.h"

#include "browser_context_qt.h"
#include "browser_context_adapter.h"
#include "content_browser_client_qt.h"
#include "web_engine_context.h"

namespace QtWebEngineCore {

using content::AccessTokenStore;
using content::BrowserThread;

AccessTokenStoreQt::AccessTokenStoreQt()
    : m_systemRequestContext(0)
{
}

AccessTokenStoreQt::~AccessTokenStoreQt()
{
}

void AccessTokenStoreQt::LoadAccessTokens(const LoadAccessTokensCallbackType& callback)
{
    BrowserThread::PostTaskAndReply(BrowserThread::UI, FROM_HERE
                , base::Bind(&AccessTokenStoreQt::performWorkOnUIThread, this)
                , base::Bind(&AccessTokenStoreQt::respondOnOriginatingThread, this, callback));
}

void AccessTokenStoreQt::performWorkOnUIThread()
{
    m_systemRequestContext = WebEngineContext::current()->defaultBrowserContext()->browserContext()->GetRequestContext();
}

void AccessTokenStoreQt::respondOnOriginatingThread(const LoadAccessTokensCallbackType& callback)
{
    callback.Run(m_accessTokenSet, m_systemRequestContext);
    m_systemRequestContext = 0;
}

void AccessTokenStoreQt::SaveAccessToken(const GURL& serverUrl, const base::string16& accessToken)
{
    m_accessTokenSet[serverUrl] = accessToken;
}

} // namespace QtWebEngineCore