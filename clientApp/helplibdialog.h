#ifndef HELPLIBDIALOG_H
#define HELPLIBDIALOG_H

#include <QDialog>

namespace Ui {
class HelpLibDialog;
}

class HelpLibDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HelpLibDialog(QWidget *parent = nullptr);
    ~HelpLibDialog();

private slots:
    void on_close_button_clicked();

    void on_parent_closed();

private:
    Ui::HelpLibDialog *ui;
};

#endif // HELPLIBDIALOG_H
