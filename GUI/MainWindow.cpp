#include "MainWindow.h"

#include <QListWidgetItem>
#include <QFileDialog>
#include <QtGui>

#include "PostureGLWidget.h"
#include "SkeletonGLWidget.h"
#include "SkeletonEditorTab.h"
#include "RenderingOptions.h"
#include "GUI/PopupWindows/Export.h"
#include "GUI/PopupWindows/Import.h"
#include "GUI/SideWidgetComponents/RenderingOptionsWidget.h"
#include "GUI/Toolbars/TransformationsToolbar.h"
#include "GUI/Toolbars/FileToolbar.h"

using namespace std;
using namespace cor3d;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    setupUi(this);
    _transformationToolbar = new TransformationsToolbar(this);
    _transformationAction = transformationToolbarUi->addWidget(_transformationToolbar);

    fileToolbarUi->addWidget(new FileToolbar(this));

    connect(_transformationToolbar, SIGNAL(viewTranslationChanged(DCoordinate3)), skeleton_editor, SLOT(viewTranslationChanged(DCoordinate3)));
    connect(_transformationToolbar, SIGNAL(viewRotationChanged(DCoordinate3)), skeleton_editor, SLOT(viewRotationChanged(DCoordinate3)));
    connect(_transformationToolbar, SIGNAL(viewZoomFactorChanged(double)), skeleton_editor, SLOT(viewZoomFactorChanged(double)));
    connect(skeleton_editor, SIGNAL(modelTransformationsChanged()), this, SLOT(updateToolbarTransformations()));
}

void MainWindow::initialize()
{
    skeleton_editor->initialize();
    posture_editor->initialize();
    scene_editor->initialize();
}

//--------------------------------
// implementation of private slots
//--------------------------------
void MainWindow::on_action_Quit_triggered()
{
    qApp->exit(0);
}


void MainWindow::on_actionRendering_options_activated()
{
    RenderingOptionsWidget *roWidget = new RenderingOptionsWidget(this);
    roWidget->setWindowTitle("Rendering Options");
    roWidget->setWindowModality(Qt::ApplicationModal);
    roWidget->setWindowFlags(Qt::Window);
    roWidget->show();

/*
    QBoxLayout *frameLayout = new QHBoxLayout();
    frameLayout->addWidget(roWidget);

    QFrame *qFrame = new QFrame(this);
    qFrame->setFrameStyle(QFrame::Sunken | QFrame::Box);
    qFrame->setGeometry(50,-2,100,15);
    qFrame->setLayout(frameLayout);
    qFrame->show();


    QDialog *dialog = new QDialog( this );
    dialog->setWindowFlags( Qt::WindowStaysOnTopHint );
                    dialog->show();


    QWidget *popup = new QWidget();
    popup->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    popup->setWindowModality(Qt::ApplicationModal);
    popup->show();
    */
}

void MainWindow::on_actionExport_triggered()
{
    Export *exportWindow = new Export(this);
    exportWindow->setWindowTitle("Export");
    exportWindow->setWindowModality(Qt::ApplicationModal);
    exportWindow->setWindowFlags(Qt::Window);
    exportWindow->show();
}

void MainWindow::on_actionImport_triggered()
{
    Import *importWindow = new Import(this);
    importWindow->setWindowTitle("Import");
    importWindow->setWindowFlags(Qt::Window);
    importWindow->show();
}

void MainWindow::on_actionTransformations_triggered(bool checked)
{
    transformationToolbarUi->setVisible(checked);
}

void MainWindow::updateToolbarTransformations()
{
    _transformationToolbar->setTranslation(((IMainWindowTab*)tabWidget->currentWidget())->glwidget->get_translation());
    _transformationToolbar->setRotation(((IMainWindowTab*)tabWidget->currentWidget())->glwidget->get_rotation());
    _transformationToolbar->setZoomFactor(((IMainWindowTab*)tabWidget->currentWidget())->glwidget->get_zoom_factor());
}
