#include "renewmemberdialog.h"
#include "ui_renewmemberdialog.h"

RenewMemberDialog::RenewMemberDialog(ServerConnection * srv, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RenewMemberDialog)
{
    ui->setupUi(this);
    server = srv;
    connect(parent, SIGNAL(closed()), this, SLOT(on_parent_closed()));
}

RenewMemberDialog::~RenewMemberDialog()
{
    delete ui;
}

void RenewMemberDialog::on_pushButton_2_clicked()
{
    close();
}
void RenewMemberDialog::on_parent_closed()
{
    close();
}
