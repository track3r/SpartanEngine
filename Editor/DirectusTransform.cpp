/*
Copyright(c) 2016 Panos Karabelas

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is furnished
to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

//===============================
#include "DirectusTransform.h"
#include "Components/Transform.h"
#include "IO/Log.h"
//===============================

using namespace Directus::Math;

DirectusTransform::DirectusTransform(QWidget *parent) : QWidget(parent)
{
    m_gridLayout = new QGridLayout();
    m_validator = new QDoubleValidator(-2147483647, 2147483647, 4);

    m_image = new QWidget(this);
    m_image->setStyleSheet("background-image: url(:/Images/transform.png); background-repeat: no-repeat; background-position: left;");
    m_title = new QLabel("Transform");

    // = POSITION =================================
    m_posLabel = new QLabel("Position");

    m_posX = CreateQLineEdit();   
    m_posY = CreateQLineEdit(); 
    m_posZ = CreateQLineEdit();

    m_posXLabel = new DirectusAdjustLabel();
    m_posXLabel->setText("X");
    m_posXLabel->AdjustQLineEdit(m_posX);
    m_posYLabel = new DirectusAdjustLabel();
    m_posYLabel->setText("Y");
    m_posYLabel->AdjustQLineEdit(m_posY);
    m_posZLabel = new DirectusAdjustLabel();
    m_posZLabel->setText("Z");
    m_posZLabel->AdjustQLineEdit(m_posZ);
    //=============================================

    //= ROTATION ==================================
    m_rotLabel = new QLabel("Rotation");

    m_rotX = CreateQLineEdit();  
    m_rotY = CreateQLineEdit();   
    m_rotZ = CreateQLineEdit();

    m_rotXLabel = new DirectusAdjustLabel();
    m_rotXLabel->setText("X");
    m_rotXLabel->AdjustQLineEdit(m_rotX);
    m_rotYLabel = new DirectusAdjustLabel();
    m_rotYLabel->setText("Y");
    m_rotYLabel->AdjustQLineEdit(m_rotY);
    m_rotZLabel = new DirectusAdjustLabel();
    m_rotZLabel->setText("Z");
    m_rotZLabel->AdjustQLineEdit(m_rotZ);
    //=============================================

    //= SCALE =====================================
    m_scaLabel = new QLabel("Scale");

    m_scaX = CreateQLineEdit();
    m_scaY = CreateQLineEdit();
    m_scaZ = CreateQLineEdit();

    m_scaXLabel = new DirectusAdjustLabel();
    m_scaXLabel->setText("X");
    m_scaXLabel->AdjustQLineEdit(m_scaX);
    m_scaYLabel = new DirectusAdjustLabel();
    m_scaYLabel->setText("Y");
    m_scaYLabel->AdjustQLineEdit(m_scaY);
    m_scaZLabel = new DirectusAdjustLabel();
    m_scaZLabel->setText("Z");
    m_scaZLabel->AdjustQLineEdit(m_scaZ);
    //=============================================

    // addWidget(*Widget, row, column, rowspan, colspan)

    // 0th row
    m_gridLayout->addWidget(m_image, 0, 0, 1, 1);
    m_gridLayout->addWidget(m_title, 0, 1, 1, 2);

    // 1st row
    m_gridLayout->addWidget(m_posLabel,    1, 0, 1, 1);
    m_gridLayout->addWidget(m_posXLabel,   1, 1, 1, 1);
    m_gridLayout->addWidget(m_posX,        1, 2, 1, 1);
    m_gridLayout->addWidget(m_posYLabel,   1, 3, 1, 1);
    m_gridLayout->addWidget(m_posY,        1, 4, 1, 1);
    m_gridLayout->addWidget(m_posZLabel,   1, 5, 1, 1);
    m_gridLayout->addWidget(m_posZ,        1, 6, 1, 1);

    // 2nd row
    m_gridLayout->addWidget(m_rotLabel,    2, 0, 1, 1);
    m_gridLayout->addWidget(m_rotXLabel,   2, 1, 1, 1);
    m_gridLayout->addWidget(m_rotX,        2, 2, 1, 1);
    m_gridLayout->addWidget(m_rotYLabel,   2, 3, 1, 1);
    m_gridLayout->addWidget(m_rotY,        2, 4, 1, 1);
    m_gridLayout->addWidget(m_rotZLabel,   2, 5, 1, 1);
    m_gridLayout->addWidget(m_rotZ,        2, 6, 1, 1);

    // 3rd row
    m_gridLayout->addWidget(m_scaLabel,    3, 0, 1, 1);
    m_gridLayout->addWidget(m_scaXLabel,   3, 1, 1, 1);
    m_gridLayout->addWidget(m_scaX,        3, 2, 1, 1);
    m_gridLayout->addWidget(m_scaYLabel,   3, 3, 1, 1);
    m_gridLayout->addWidget(m_scaY,        3, 4, 1, 1);
    m_gridLayout->addWidget(m_scaZLabel,   3, 5, 1, 1);
    m_gridLayout->addWidget(m_scaZ,        3, 6, 1, 1);

   // Connect textEdit(QString) signal with the appropriate slot
   // NOTE: Unlike textChanged(), this signal is not emitted when the
   // text is changed programmatically, for example, by calling setText().
   connect(m_posX, SIGNAL(textChanged(QString)), this, SLOT(UpdateEnginePos()));
   connect(m_posY, SIGNAL(textChanged(QString)), this, SLOT(UpdateEnginePos()));
   connect(m_posZ, SIGNAL(textChanged(QString)), this, SLOT(UpdateEnginePos()));
   connect(m_rotX, SIGNAL(textChanged(QString)), this, SLOT(UpdateEngineRot()));
   connect(m_rotY, SIGNAL(textChanged(QString)), this, SLOT(UpdateEngineRot()));
   connect(m_rotZ, SIGNAL(textChanged(QString)), this, SLOT(UpdateEngineRot()));
   connect(m_scaX, SIGNAL(textChanged(QString)), this, SLOT(UpdateEngineSca()));
   connect(m_scaY, SIGNAL(textChanged(QString)), this, SLOT(UpdateEngineSca()));
   connect(m_scaZ, SIGNAL(textChanged(QString)), this, SLOT(UpdateEngineSca()));

   this->setParent(parent);
   this->setLayout(m_gridLayout);
   this->show(); // This is not a mistake, it helps
   this->hide(); // get the widget fully initialized
}

void DirectusTransform::Map(GameObject* gameobject)
{
    m_inspectedTransform = nullptr;

    // Catch evil case
    if (!gameobject)
    {
        this->hide();
        return;
    }

    // Catch the seed of the evil
    m_inspectedTransform = gameobject->GetTransform();
    if (!m_inspectedTransform)
    {
        this->hide();
        return;
    }

    // Do the actual mapping
    SetPosition(m_inspectedTransform->GetPositionLocal());
    SetRotation(m_inspectedTransform->GetRotationLocal());
    SetScale(m_inspectedTransform->GetScaleLocal());

    // Make this widget visible
    this->show();
}

Vector3 DirectusTransform::GetPosition()
{
    float x = m_posX->text().toFloat();
    float y = m_posY->text().toFloat();
    float z = m_posZ->text().toFloat();

    return Vector3(x, y, z);
}

void DirectusTransform::SetPosition(Vector3 pos)
{
    m_posX->setText(QString::number(pos.x));
    m_posY->setText(QString::number(pos.y));
    m_posZ->setText(QString::number(pos.z));
}

Quaternion DirectusTransform::GetRotation()
{
    float x = m_rotX->text().toFloat();
    float y = m_rotY->text().toFloat();
    float z = m_rotZ->text().toFloat();

    return Quaternion::FromEulerAngles(x, y, z);
}

void DirectusTransform::SetRotation(Quaternion rot)
{
    SetRotation(rot.ToEulerAngles());
}

void DirectusTransform::SetRotation(Vector3 rot)
{
    m_rotX->setText(QString::number(rot.x));
    m_rotY->setText(QString::number(rot.y));
    m_rotZ->setText(QString::number(rot.z));
}

Vector3 DirectusTransform::GetScale()
{
    float x = m_scaX->text().toFloat();
    float y = m_scaY->text().toFloat();
    float z = m_scaZ->text().toFloat();

    return Vector3(x, y, z);
}

void DirectusTransform::SetScale(Vector3 sca)
{
    m_scaX->setText(QString::number(sca.x));
    m_scaY->setText(QString::number(sca.y));
    m_scaZ->setText(QString::number(sca.z));
}

QLineEdit* DirectusTransform::CreateQLineEdit()
{
    QLineEdit* lineEdit = new QLineEdit();
    lineEdit->setValidator(m_validator);

    return lineEdit;
}

void DirectusTransform::UpdateEnginePos()
{
    if (!m_inspectedTransform)
        return;

    m_inspectedTransform->SetPositionLocal(GetPosition());
}

void DirectusTransform::UpdateEngineRot()
{
    if (!m_inspectedTransform)
        return;

    m_inspectedTransform->SetRotationLocal(GetRotation());
}

void DirectusTransform::UpdateEngineSca()
{
    if (!m_inspectedTransform)
        return;

    m_inspectedTransform->SetScaleLocal(GetScale());
}
