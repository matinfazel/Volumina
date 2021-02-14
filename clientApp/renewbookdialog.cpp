#include "renewbookdialog.h"
#include "ui_renewbookdialog.h"

RenewBookDialog::RenewBookDialog(ServerConnection * srv, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RenewBookDialog)
{
    ui->setupUi(this);
    server = srv;
    connect(parent, SIGNAL(closed()), this, SLOT(on_parent_closed()));
}

RenewBookDialog::~RenewBookDialog()
{
    delete ui;
}

void RenewBookDialog::on_pushButton_2_clicked()
{
    close();
}

void RenewBookDialog::on_parent_closed()
{
    close();
}
