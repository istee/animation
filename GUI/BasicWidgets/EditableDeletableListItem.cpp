#include "EditableDeletableListItem.h"
#include "ui_EditableDeletableListItem.h"

#include <iostream>

using namespace std;

EditableDeletableListItem::EditableDeletableListItem(const std::string& labelText, BaseSideWidget* editWidget, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditableDeletableListItem)
{
    ui->setupUi(this);
    ui->label->setText(QString::fromStdString(labelText));
    ui->lineEdit->setVisible(false);
    _sizeHint = QSize(100, 40);

    _isRenameActive = false;
    _isEditActive = false;
    _editWidget = editWidget;
    _editWidget->setVisible(false);
    ui->verticalLayout->addWidget(editWidget);
}

void EditableDeletableListItem::setLabelText(const string& text)
{
    ui->label->setText(QString::fromStdString(text));
}

string EditableDeletableListItem::labelText() const
{
    return ui->label->text().toStdString();
}

string EditableDeletableListItem::lineEditText() const
{
    return ui->lineEdit->text().toStdString();
}

void EditableDeletableListItem::showEditWidget(bool show)
{
    _isEditActive = show;
    _editWidget->setVisible(_isEditActive);
    if (_isEditActive)
    {
        _editWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    }
}

bool EditableDeletableListItem::isEditWidgetVisible()
{
    return _isEditActive;
}

BaseSideWidget* EditableDeletableListItem::editWidget()
{
    return _editWidget;
}

void EditableDeletableListItem::showRename(bool show)
{
    ui->toolButtonRename->setVisible(show);
}

void EditableDeletableListItem::showEdit(bool show)
{
    ui->toolButtonEdit->setVisible(show);
}

void EditableDeletableListItem::showDelete(bool show)
{
    ui->toolButtonDelete->setVisible(show);
}

QSize EditableDeletableListItem::sizeHint() const
{
    if (_isEditActive)
    {
        return QSize(_sizeHint.width(), _sizeHint.height() + _editWidget->sizeHint().height());
    }
    else
    {
        return _sizeHint;
    }
}

QSize EditableDeletableListItem::minimumSizeHint() const
{
    if (_isEditActive)
    {
        return QSize(100, 200);
    }
    else
    {
        return QSize(100, 40);
    }
}

EditableDeletableListItem::~EditableDeletableListItem()
{
    delete ui;
}

void EditableDeletableListItem::on_toolButtonDelete_clicked()
{
    emit view_list_item_deleted(ui->label->text().toStdString());
}

void EditableDeletableListItem::handleRename()
{
    _isRenameActive = !_isRenameActive;

    if (_isRenameActive)
    {
        ui->label->setVisible(false);
        ui->lineEdit->setText(ui->label->text());
        ui->lineEdit->setVisible(true);
        ui->lineEdit->setFocus();
    }
    else
    {
        ui->lineEdit->setVisible(false);
        ui->label->setVisible(true);
        if (ui->label->text() != ui->lineEdit->text())
        {
            emit view_list_item_renamed(ui->label->text().toStdString(), ui->lineEdit->text().toStdString());
        }
    }
}

void EditableDeletableListItem::setVisible(bool visible)
{
    QWidget::setVisible(visible);
    ui->lineEdit->setVisible(visible && _isRenameActive);
    _editWidget->setVisible(visible && _isEditActive);
}

void EditableDeletableListItem::on_toolButtonRename_clicked()
{
    handleRename();
}

void EditableDeletableListItem::on_lineEdit_returnPressed()
{
    handleRename();
}

void EditableDeletableListItem::on_toolButtonEdit_clicked()
{
    emit view_list_item_edited(ui->label->text().toStdString());
}
