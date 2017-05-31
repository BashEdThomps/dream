/*
 * MainController.cpp
 *
 * Created: 14 2017 by Ashley
 *
 * Copyright 2017 Octronic. All rights reserved.
 *
 * This file may be distributed under the terms of GNU Public License version
 * 3 (GPL v3) as defined by the Free Software Foundation (FSF). A copy of the
 * license should have been included with this file, or the project in which
 * this file belongs to. You may also find the details of GPL v3 at:
 * http://www.gnu.org/licenses/gpl-3.0.txt
 *
 * If you have any questions regarding the use of this file, feel free to
 * contact the author of this file, or the owner of the project in which
 * this file belongs to.
 */
#include "MainController.h"

#include <QDebug>
#include <QFileDialog>
#include <QErrorMessage>
#include <QModelIndexList>
#include <DreamCore.h>
#include <QOpenGLContext>

#include "../Model/TreeModels/Properties/AssetDefinitionPropertiesModel.h"
#include "../Model/TreeModels/Properties/PropertiesModel.h"
#include "../Model/TreeModels/Properties/ProjectPropertiesModel.h"
#include "../Model/TreeModels/Properties/SceneObjectPropertiesModel.h"
#include "../Model/TreeModels/Properties/ScenePropertiesModel.h"
#include "../Model/TreeModels/Properties/AssetDefinitionTypeComboDelegate.h"

MainController::MainController
(MainWindow* parent)
    : QObject(parent)
{
    mMainWindow = parent;
    mWindowComponent = parent->getWindowComponent();
    mDreamModel = new DreamModel(this,mWindowComponent);
    createConnections();
}

MainController::~MainController
()
{
    if (mDreamModel)
    {
        delete mDreamModel;
        mDreamModel = nullptr;
    }
}

void
MainController::createConnections
()
{
    // actionNew
    connect
    (
        mMainWindow->getActionNew(), SIGNAL(triggered()),
        this, SLOT(onProjectNewButtonClicked())
    );
    // actionOpen
    connect
    (
        mMainWindow->getActionOpen(), SIGNAL(triggered()),
        this, SLOT(onProjectOpenButtonClicked())
    );
    // actionSave
    connect
    (
        mMainWindow->getActionSave(), SIGNAL(triggered()),
        this, SLOT(onProjectSaveButtonClicked())
    );
    // actionReload
    connect
    (
        mMainWindow->getActionReload(), SIGNAL(triggered()),
        this, SLOT(onProjectReloadButtonClicked())
    );
    // actionPlay
    connect
    (
                mMainWindow->getActionPlay(), SIGNAL(triggered()),
                this, SLOT(onProjectPlayButtonClicked())
    );
    // actionStop
    connect
    (
                mMainWindow->getActionStop(), SIGNAL(triggered()),
                this, SLOT(onProjectStopButtonClicked())
    );
    connect
    (
                this,SIGNAL(notifyStoppedScene(Dream::Scene*)),
                mMainWindow,SLOT(onSceneStopped(Dream::Scene*))
    );
    // Invalid Project Directory
    connect
    (
        this, SIGNAL(notifyInvalidProjectDirectory(QString)),
        mMainWindow, SLOT(onInvalidProjectDirectory(QString))
    );
    // No Scene Selected
    connect
    (
        this,SIGNAL(notifyNoSceneSelected()),
        mMainWindow, SLOT(onNoSceneSelected())
    );
    // Valid Scene Selected
    connect
    (
                mDreamModel, SIGNAL(notifySelectedSceneChanged(Dream::Scene*)),
                this, SLOT(onSelectedSceneChanged(Dream::Scene*))
    );
    // Project Directory Changed
    connect
    (
        this, SIGNAL(notifyProjectDirectoryChanged(QString)),
        mMainWindow, SLOT(setWindowTitle(QString))
     );
    // Status Bar
    connect
    (
        this, SIGNAL(notifyStatusBarProjectLoaded(QString)),
        mMainWindow, SLOT(showStatusBarMessage(QString))
     );
}

void
MainController::onProjectNewButtonClicked
()
{
    QFileDialog openDialog;
    openDialog.setFileMode(QFileDialog::Directory);

    if(openDialog.exec())
    {
    }
}

void
MainController::updateWindowTitle
(QString msg)
{
    emit notifyProjectDirectoryChanged("Dream Tool :: " + msg);
}

void
MainController::onProjectOpenButtonClicked
()
{
    QFileDialog openDialog;
    openDialog.setFileMode(QFileDialog::Directory);

    if(openDialog.exec())
    {
        mProjectDirectory = openDialog.selectedFiles().first();
    }

    if (mProjectDirectory.size() == 0)
    {
        return;
    }

    bool loadResult = mDreamModel->loadProject(mProjectDirectory);
    cout << "LoadResult " << loadResult << endl;
    if (!loadResult)
    {
        emit notifyInvalidProjectDirectory(mProjectDirectory);
        emit notifyProjectWidgetsEnabledChanged(false);
        return;
    }
    updateWindowTitle(mProjectDirectory);
    Dream::Project *currentProject = mDreamModel->getProject();

    emit notifyProjectNameChanged(QString::fromStdString(currentProject->getName()));
    emit notifyProjectAuthorChanged(QString::fromStdString(currentProject->getAuthor()));
    emit notifyProjectDescriptionChanged(QString::fromStdString(currentProject->getDescription()));
    emit notifyProjectWindowWidthChanged(currentProject->getWindowWidth());
    emit notifyProjectWindowHeightChanged(currentProject->getWindowHeight());
    emit notifyProjectSceneListChanged(getSceneNamesListModel(currentProject->getSceneList()));
    emit notifyProjectStartupSceneChanged(QString::fromStdString(currentProject->getStartupScene()->getName()));
    emit notifyProjectWidgetsEnabledChanged(true);
    Dream::Project *project = mDreamModel->getProject();

    mProjectTreeModel = new ProjectTreeModel(project,mMainWindow->getProjectTreeView());
    mMainWindow->getProjectTreeView()->setModel(mProjectTreeModel);

    mAssetDefinitionTreeModel = new AssetDefinitionTreeModel(project,mMainWindow->getAssetDefinitionTreeView());
    mMainWindow->getAssetDefinitionTreeView()->setModel(mAssetDefinitionTreeModel);

    emit notifyStatusBarProjectLoaded(
                QString::fromStdString(
                    "Successfuly Loaded Project: " +
                    project->getName() + " (" +
                    project->getUuid() + ")"
                    )
                );
    connectTreeViewModel();
}

void
MainController::connectTreeViewModel
()
{
    // projectTreeView
    connect
    (
        mMainWindow->getProjectTreeView()->selectionModel(),
        SIGNAL(selectionChanged(const QItemSelection&,const QItemSelection&)),
        this, SLOT(onTreeViewSelectionChanged(const QItemSelection&,const QItemSelection&))
    );
    // assetDefinitionTreeView
    connect
    (
        mMainWindow->getAssetDefinitionTreeView()->selectionModel(),
        SIGNAL(selectionChanged(const QItemSelection&,const QItemSelection&)),
        this, SLOT(onTreeViewSelectionChanged(const QItemSelection&,const QItemSelection&))
    );
    mMainWindow->getProjectTreeView()->expandAll();
    mMainWindow->getAssetDefinitionTreeView()->expandAll();
}

void
MainController::onProjectSaveButtonClicked
()
{
    QFileDialog openDialog;
    openDialog.setFileMode(QFileDialog::Directory);

    if(openDialog.exec())
    {
    }
}

QStringListModel*
MainController::getSceneNamesListModel
(vector<Dream::Scene*> sceneList)
{
    QStringList sceneNameList;
    mSceneListModel = new QStringListModel(mMainWindow);

    for (auto scene : sceneList)
    {
        sceneNameList.push_back(QString::fromStdString(scene->getName()));
    }

    mSceneListModel->setStringList(sceneNameList);
    return mSceneListModel;
}

void
MainController::onProjectNameChanged
(QString name)
{
    qDebug() << "Name set to " << name;
    mDreamModel->setProjectName(name.toStdString());
}

void
MainController::onProjectAuthorChanged
(QString author)
{
    qDebug() << "Author set to " << author;
    mDreamModel->setProjectAuthor(author.toStdString());
}

void
MainController::onProjectDescriptionChanged
(QString desc)
{
    qDebug() << "Description set to " << desc;
    mDreamModel->setProjectDescription(desc.toStdString());
}

void
MainController::onProjectWindowWidthChanged
(QString width)
{
    qDebug() << "Window Width set to " << width;
    mDreamModel->setProjectWindowWidth(width.toInt());
}

void
MainController::onProjectWindowHeightChanged
(QString height)
{
    qDebug() << "Window Height set to " << height;
    mDreamModel->setProjectWindowHeight(height.toInt());
}

void
MainController::onProjectStartupSceneChanged
(QString startupSceneIndex)
{
    string sceneName = getSceneNameFromModelIndex(startupSceneIndex.toInt());
    qDebug() << "startupScene set to " << startupSceneIndex << " " << QString::fromStdString(sceneName);
    mDreamModel->setProjectStartupSceneByName(sceneName);
}

void
MainController::onProjectPlayButtonClicked
()
{
    qDebug() << "onReloadProject Clicked";
    Dream::Scene *scene = mDreamModel->getSelectedScene();
    if (scene)
    {
        mDreamModel->startScene(mDreamModel->getSelectedScene());
        emit notifyPlayingScene(scene);
    }
    else
    {
        emit notifyNoSceneSelected();
    }
}

void
MainController::onProjectReloadButtonClicked
()
{
   onProjectStopButtonClicked();
   onProjectPlayButtonClicked();
}

void
MainController::onProjectStopButtonClicked
()
{
    Dream::Scene* scene = mDreamModel->stopActiveScene();
    emit notifyStoppedScene(scene);
}

string
MainController::getSceneNameFromModelIndex
(int index)
{
    return mSceneListModel->stringList().at(index).toStdString();
}

void
MainController::onTreeViewSelectionChanged
(const QItemSelection& selected,const QItemSelection& deselected)
{
    QModelIndexList indexes = selected.indexes();
    if (indexes.size() > 0)
    {
        GenericTreeItem *selected = static_cast<GenericTreeItem*>(indexes.at(0).internalPointer());
        setupPropertiesTreeViewModel(selected);
        mMainWindow->getPropertiesTreeView()->expandAll();
    }
}

void
MainController::setupPropertiesTreeViewModel
(GenericTreeItem *item)
{
    QTreeView *propertiesTreeView = mMainWindow->getPropertiesTreeView();
    PropertiesModel *model = nullptr;
    Dream::Project *project = nullptr;
    Dream::AssetDefinition *asset = nullptr;
    Dream::Scene *scene = nullptr;
    Dream::SceneObject *sceneObject = nullptr;

    switch(item->getItemType())
    {
        case GenericTreeItemType::PROJECT:
            qDebug() << "Selected a project";
            project = mDreamModel->getProject();
            model = new ProjectPropertiesModel(project,propertiesTreeView);
            break;
        case GenericTreeItemType::ASSET_DEFINITION:
            qDebug() << "Selected an asset definition";
            asset = static_cast<AssetDefinitionTreeItem*>(item)->getAssetDefinition();
            model = new AssetDefinitionPropertiesModel(asset,propertiesTreeView);
            // Set Type Delegate
            break;
        case GenericTreeItemType::SCENE:
            scene = static_cast<Dream::Scene*>(static_cast<ProjectTreeItem*>(item)->getItem());
            mDreamModel->setSelectedScene(scene);
            if (scene)
            {
                model = new ScenePropertiesModel(scene,propertiesTreeView);
                qDebug() << "Selected a scene";
            }
            break;
        case GenericTreeItemType::SCENE_OBJECT:
            qDebug() << "Selected a scene object";
            sceneObject = static_cast<Dream::SceneObject*>(static_cast<ProjectTreeItem*>(item)->getItem());
            model = new SceneObjectPropertiesModel(sceneObject,propertiesTreeView);
            break;
        case GenericTreeItemType::TREE_NODE:
            qDebug() << "Selected a tree node";
            break;
    }

    if (model)
    {
        propertiesTreeView->setModel(model);
    }
}

void MainController::onSelectedSceneChanged(Dream::Scene *scene)
{
    mMainWindow->showStatusBarMessage(
        QString("Selected Scene: %1").
            arg(QString::fromStdString(scene->getName())
        )
    );
}
