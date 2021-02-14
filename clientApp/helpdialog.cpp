#include "helpdialog.h"
#include "ui_helpdialog.h"

HelpDialog::HelpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpDialog)
{
    ui->setupUi(this);
    connect(parent, SIGNAL(closed()), this, SLOT(on_parent_closed()));
}

HelpDialog::~HelpDialog()
{
    delete ui;
}

void HelpDialog::on_close_button_clicked()
{
    close();
}

void HelpDialog::on_parent_closed()
{
    close();
}
