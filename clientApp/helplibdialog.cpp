#include "helplibdialog.h"
#include "ui_helplibdialog.h"

HelpLibDialog::HelpLibDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpLibDialog)
{
    ui->setupUi(this);
    connect(parent, SIGNAL(closed()), this, SLOT(on_parent_closed()));
}

HelpLibDialog::~HelpLibDialog()
{
    delete ui;
}

void HelpLibDialog::on_close_button_clicked()
{
    close();
}

void HelpLibDialog::on_parent_closed()
{
    close();
}
