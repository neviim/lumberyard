/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
* its licensors.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/

#include <AzCore/base.h>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QCompleter>
#include "AzToolsFramework/UI/UICore/PlainTextEdit.hxx"
#include <AzCore/std/functional.h>

#pragma once

namespace LUAEditor
{
    class LUAEditorPlainTextEdit : public AzToolsFramework::PlainTextEdit
    {
        Q_OBJECT

    public:
        AZ_CLASS_ALLOCATOR(LUAEditorPlainTextEdit, AZ::SystemAllocator, 0);

        LUAEditorPlainTextEdit(QWidget *pParent = nullptr);
        virtual ~LUAEditorPlainTextEdit();
        
        void UpdateFont(QFont font, int tabSize);
        void SetGetLuaName(AZStd::function<QString(const QTextCursor&)> lambda) { m_getLUAName = lambda; }

    protected:
        void focusInEvent(QFocusEvent* pEvent) override;
        void focusOutEvent(QFocusEvent* pEvent) override;
        void paintEvent(QPaintEvent*) override;
        void keyPressEvent(QKeyEvent* event) override;
        void wheelEvent(QWheelEvent* event) override;
        void dropEvent(QDropEvent *e) override;

    private:
        class Completer* m_completer;
        class CompletionModel* m_completionModel;
        AZStd::function<QString(const QTextCursor&)> m_getLUAName;

        bool HandleIndentKeyPress(QKeyEvent* event);
        bool HandleHomeKeyPress(QKeyEvent* event);
        bool HandleNewline(QKeyEvent* event);

    signals:
        void FocusChanged(bool focused);
        void ZoomIn();
        void ZoomOut();

    public slots:
        void OnScopeNamesUpdated(const QStringList& scopeNames);

    private slots:
        void CompletionSelected(const QString& text);
    };
}