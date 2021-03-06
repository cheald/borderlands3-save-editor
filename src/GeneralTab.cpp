#include "GeneralTab.h"

#include "Savegame.h"
#include "Constants.h"
#include "Lol.h"

#include <QSpinBox>
#include <QGroupBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFontDatabase>

GeneralTab::GeneralTab(Savegame *savegame, QWidget *parent) :
    QWidget(parent)
{
    setLayout(new QVBoxLayout);

    //////////////////////////
    // Basic properties
    QGroupBox *basicsBox = new QGroupBox(tr("Basics"));
    QFormLayout *basicsLayout = new QFormLayout;
    basicsLayout->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);
    basicsBox->setLayout(basicsLayout);

    m_nameEdit = new QLineEdit;
    basicsLayout->addRow(tr("Name"), m_nameEdit);

    m_levelEdit = new QSpinBox;
    m_levelEdit->setRange(Constants::minLevel, Constants::maxLevel);
    basicsLayout->addRow(tr("Level"), m_levelEdit);

    m_xpEdit = new QSpinBox;
    m_xpEdit->setRange(0, Constants::requiredXp[Constants::maxLevel]);
    m_xpEdit->setSingleStep(1000);
    basicsLayout->addRow(tr("Experience points"), m_xpEdit);

    layout()->addWidget(basicsBox);

    connect(savegame, &Savegame::nameChanged, m_nameEdit, &QLineEdit::setText);
    connect(savegame, &Savegame::levelChanged, m_levelEdit, &QSpinBox::setValue);
    connect(savegame, &Savegame::xpChanged, m_xpEdit, &QSpinBox::setValue);

    connect(m_nameEdit, &QLineEdit::textEdited, savegame, &Savegame::setCharacterName);
    connect(m_levelEdit, SIGNAL(valueChanged(int)), savegame, SLOT(setLevel(int))); // old style connect because fuck qOverload
    connect(m_xpEdit, SIGNAL(valueChanged(int)), savegame, SLOT(setXp(int))); // old style connect because fuck qOverload

    // Advanced shit
    QGroupBox *advancedBox = new QGroupBox(tr("Advanced"));
    QFormLayout *advancedLayout = new QFormLayout;
    advancedLayout->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);
    advancedBox->setLayout(advancedLayout);
    m_saveSlot = new QSpinBox;
    m_saveSlot->setMinimum(1);
    m_saveSlot->setMaximum(10); // lolidk
    advancedLayout->addRow(tr("Save slot"), m_saveSlot);
    m_uuid = new QLabel("UUID");
    m_uuid->setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));
    advancedLayout->addRow(tr("UUID"), m_uuid);
    QPushButton *generateUuidButton = new QPushButton(tr("Generate random UUID"));
    advancedLayout->addWidget(generateUuidButton);

    layout()->addWidget(advancedBox);

    layout()->addWidget(new Lol);

    connect(savegame, &Savegame::saveSlotChanged, m_saveSlot, &QSpinBox::setValue);
    connect(savegame, &Savegame::uuidChanged, m_uuid, &QLabel::setText);
    connect(m_saveSlot, SIGNAL(valueChanged(int)), savegame, SLOT(setSaveSlot(int))); // old style connect because fuck qOverload
    connect(generateUuidButton, &QPushButton::clicked, savegame, &Savegame::regenerateUuid);
}
