#include "ProjectDirectory.h"

#include "Project/ProjectDefinition.h"
#include "Project/Project.h"
#include "Common/Logger.h"
#include "Common/Constants.h"
#include "Components/AssetDefinition.h"
#include "Directory.h"
#include "StorageManager.h"

#include <sstream>

using std::stringstream;

namespace octronic::dream
{
    ProjectDirectory::ProjectDirectory(StorageManager* fileManager)
        : mProject(nullptr),
          mStorageManager(fileManager)
    {
        LOG_TRACE("ProjectDirectory: {}", __FUNCTION__);
    }

    ProjectDirectory::ProjectDirectory
    (StorageManager* fileManager, Project* proj)
        : mProject(proj),
          mStorageManager(fileManager)
    {
        LOG_TRACE("ProjectDirectory: {}", __FUNCTION__);
    }

    ProjectDirectory::~ProjectDirectory
    ()
    {
        LOG_TRACE("ProjectDirectory: {}", __FUNCTION__);
        closeProject();
    }

    bool
    ProjectDirectory::baseDirectoryExists
    ()
    const
    {
        Directory* d = mStorageManager->openDirectory(mPath);
        bool retval = d->exists();
        mStorageManager->closeDirectory(d);
        return retval;
    }

    bool
    ProjectDirectory::createBaseDirectory
    ()
    const
    {
        LOG_DEBUG("ProjectDirectory: Creating project directory {}",mPath);
        Directory* d = mStorageManager->openDirectory(mPath);
        if(!d->create())
        {
            LOG_ERROR("ProjectDirectory: Unable to create project directory {}",mPath);
            mStorageManager->closeDirectory(d);
            d = nullptr;
            return false;
        }
        mStorageManager->closeDirectory(d);
        d = nullptr;
        return true;
    }

    bool
    ProjectDirectory::createAllAssetDirectories
    ()
    const
    {
        auto assetTypes = Constants::DREAM_ASSET_TYPES_MAP;
        for (const auto& typePair : assetTypes)
        {
            auto type = typePair.first;
            if (!createAssetTypeDirectory(type))
            {
                LOG_ERROR("ProjectDirectory: Unable to create asset directory {}",Constants::getAssetTypeStringFromTypeEnum(type));
                return false;
            }
        }
        return true;
    }

    File*
    ProjectDirectory::readAssetData
    (AssetDefinition* assetDef, const string &format)
    const
    {
        auto path = getAssetAbsolutePath(assetDef,format);
        File* f = mStorageManager->openFile(path);
        return f;
    }

    bool
    ProjectDirectory::writeAssetData
    (AssetDefinition* assetDef, uint8_t* data, size_t data_size, const string& format)
    const
    {
        auto dataPath = getAssetDirectoryPath(assetDef);
        LOG_DEBUG("ProjectDirectory: Writing asset data to {}",dataPath);

        //Check target directory exists
        Directory* dir = mStorageManager->openDirectory(dataPath);
        if (!dir->exists())
        {
            LOG_DEBUG("ProjectDirectory: Asset path does not exist {}",dataPath);
            auto assetTypeEnum = Constants::getAssetTypeEnumFromString(assetDef->getType());
            if (!assetTypeDirectoryExists(assetTypeEnum))
            {
                if(!createAssetTypeDirectory(assetTypeEnum))
                {
                    LOG_ERROR("ProjectDirectory: Unable to create asset type directory");
                    return false;
                }
            }
            if(!dir->create())
            {
                LOG_ERROR("ProjectDirectory: Unable to create asset path {}",dataPath);
                return false;
            }
        }
        auto path = getAssetAbsolutePath(assetDef,format);
        LOG_DEBUG("ProjectDirectory: Copying asset to {}",path);
        File* file = mStorageManager->openFile(path);
        bool retval = file->writeBinary(data, data_size);
        mStorageManager->closeFile(file);
        return retval;
    }

    string
    ProjectDirectory::getAssetAbsolutePath
    (UuidType uuid)
    const
    {
        auto assetDef = mProject->getDefinition()->getAssetDefinitionByUuid(uuid);
        if (assetDef)
        {
            stringstream path;
            path << mPath
                 << Constants::DIR_PATH_SEP
                 << assetDef->getType()
                 << Constants::DIR_PATH_SEP
                 << assetDef->getUuid()
                 << Constants::DIR_PATH_SEP
                 << assetDef->getFormat();
            return path.str();
        }
        return "";
    }


    string
    ProjectDirectory::getAssetAbsolutePath
    (AssetDefinition* assetDef, const string& format)
    const
    {
        stringstream path;
        path << mPath
             << Constants::DIR_PATH_SEP
             << assetDef->getType()
             << Constants::DIR_PATH_SEP
             << assetDef->getUuid()
             << Constants::DIR_PATH_SEP
             << (format.empty() ? assetDef->getFormat() : format);
        return path.str();

    }

    string
    ProjectDirectory::getAssetAbsolutePath
    (AssetDefinition* assetDef)
    const
    {
        return getAssetAbsolutePath(assetDef,"");
    }


    string
    ProjectDirectory::getAssetDirectoryPath
    (AssetDefinition* assetDef)
    const
    {
        stringstream path;
        path << mPath
             << Constants::DIR_PATH_SEP
             << assetDef->getType()
             << Constants::DIR_PATH_SEP
             << assetDef->getUuid();
        return path.str();

    }

    bool
    ProjectDirectory::removeAssetDirectory
    (AssetDefinition* ad)
    const
    {
        auto path = getAssetDirectoryPath(ad);
        LOG_DEBUG("ProjectDirectory: Removing asset directory {}",path);
        Directory* d =  mStorageManager->openDirectory(path);
        bool retval =  d->deleteDirectory();
        mStorageManager->closeDirectory(d);
        d = nullptr;
        return retval;
    }

    bool
    ProjectDirectory::saveProject
    ()
    const
    {
        auto pDef = mProject->getDefinition();
        if (pDef)
        {
            auto jsDef = pDef->toJson();
            auto jsonStr = jsDef.dump(1);
            auto path = getProjectFilePath();
            File* f = mStorageManager->openFile(path);
            bool retval = f->writeString(jsonStr);
            mStorageManager->closeFile(f);
            f = nullptr;
            return retval;
        }
        return false;
    }

    string
    ProjectDirectory::getProjectFilePath
    ()
    const
    {
        stringstream ss;
        ss << mPath
           << Constants::DIR_PATH_SEP
           << mProject->getDefinition()->getUuid()
           << Constants::PROJECT_EXTENSION;
        return ss.str();
    }

    bool
    ProjectDirectory::assetTypeDirectoryExists
    (AssetType type)
    const
    {
        string dirPath = getAssetTypeDirectory(type);
        Directory* dir = mStorageManager->openDirectory(dirPath);
        bool retval = dir->exists();
        mStorageManager->closeDirectory(dir);
        return retval;
    }

    string
    ProjectDirectory::getAssetTypeDirectory
    (AssetType type, const string& base)
    const
    {
        stringstream ss;
        ss << (base.empty() ? mPath : base)
           << Constants::DIR_PATH_SEP
           << Constants::getAssetTypeStringFromTypeEnum(type);
        return ss.str();
    }

    bool
    ProjectDirectory::createAssetTypeDirectory
    (AssetType type)
    const
    {
        string assetTypeDirPath = getAssetTypeDirectory(type);
        Directory *dir = mStorageManager->openDirectory(assetTypeDirPath);
        LOG_DEBUG("ProjectDirectory: Creating asset dir {}", assetTypeDirPath);
        bool retval = dir->create();
        mStorageManager->closeDirectory(dir);
        return retval;
    }

    vector<string>
    ProjectDirectory::cleanupAssetsDirectory
    ()
    const
    {
        vector<string> retval;
        auto pDef = mProject->getDefinition();
        if (!pDef)
        {
            LOG_ERROR("ProjectDirectory: Cannot cleanup, no project definition");
            return retval;
        }

        for (const auto& typePair : Constants::DREAM_ASSET_TYPES_MAP)
        {
            AssetType type = typePair.first;
            string typeStr = Constants::getAssetTypeStringFromTypeEnum(type);
            string path = getAssetTypeDirectory(type);
            Directory* assetDir = mStorageManager->openDirectory(path);
            if (assetDir->exists())
            {
                vector<string> subdirs = assetDir->listSubdirectories();
                LOG_DEBUG("ProjectDirectory: Cleaning up {} containing {} definitions", path, subdirs.size());
                int deletedCount=0;

                for (string& subdirPath : subdirs)
                {
                    Directory* subdir = mStorageManager->openDirectory(subdirPath);
                    if (subdir->exists())
                    {
                        UuidType name = static_cast<UuidType>(std::stoi(subdir->getName()));
                        LOG_DEBUG("ProjectDirectory: Checking subdir {} has definition",name);
                        AssetDefinition* def = pDef->getAssetDefinitionByUuid(name);
                        if (!def)
                        {
                            LOG_DEBUG("ProjectDirectory: Definition {} does not exist, removing...",name);
                            subdir->deleteDirectory();
                            retval.push_back(subdirPath);
                        }
                    }
                    mStorageManager->closeDirectory(subdir);
                    subdir = nullptr;
                }
                LOG_DEBUG("ProjectDirectory: Deleted {}/{} {} asset directories",deletedCount,subdirs.size(),typeStr);
            }
            else
            {
                LOG_DEBUG("ProjectDirectory: No Directory {}",path);
            }
            mStorageManager->closeDirectory(assetDir);
            assetDir = nullptr;
        }
        return retval;
    }

    Project*
    ProjectDirectory::newProject
    (Directory* projectDir)
    {
        if (mProject)
        {
            closeProject();
        }

        if (directoryContainsProject(projectDir))
        {
            return nullptr;
        }

        mProject = new Project(this, mStorageManager);
        mProject->setDefinition(ProjectDefinition::createNewProjectDefinition());
        mPath = projectDir->getPath();

        if(!baseDirectoryExists())
        {
            createBaseDirectory();
        }

        createAllAssetDirectories();

        saveProject();
        return mProject;

    }

    Project*
    ProjectDirectory::openFromFile
    (File* file)
    {
        LOG_DEBUG("ProjectDirectory: Loading project from FileReader", file->getPath());

        string projectJsonStr = file->readString();

        if (projectJsonStr.empty())
        {
            LOG_ERROR("ProjectDirectory: Loading Failed. Project Content is Empty");
            return nullptr;
        }

        json projectJson;
        try
        {
            projectJson = json::parse(projectJsonStr);
        }
        catch (const json::parse_error& ex)
        {
            LOG_ERROR("ProjectDirectory: Exception while parsing project file: {}",ex.what());
            return nullptr;
        }

        mPath = file->getDirectory();
        LOG_DEBUG("ProjectDirectory: Project path is: \"{}\"", mPath);
        mProject = new Project(this, mStorageManager);
        auto pDef = new ProjectDefinition(projectJson);
        mProject->setDefinition(pDef);
        pDef->loadChildDefinitions();
        return mProject;

    }

    Project*
    ProjectDirectory::openFromDirectory
    (Directory* directory)
    {
        string projectFileName = findProjectFileInDirectory(directory);

        if (projectFileName.empty())
        {
            LOG_ERROR( "ProjectDirectory: Project: Error {} is not a valid project directory!", directory->getPath()  );
            return nullptr;
        }

        LOG_DEBUG( "ProjectDirectory: Project: Loading {}{} from Directory {}", projectFileName , Constants::PROJECT_EXTENSION , directory->getPath());

        string projectFilePath = directory->getPath() + Constants::PROJECT_PATH_SEP + projectFileName + Constants::PROJECT_EXTENSION;

        File* projectFile = mStorageManager->openFile(projectFilePath);

        Project* retval = openFromFile(projectFile);
        mStorageManager->closeFile(projectFile);
        projectFile = nullptr;

        return retval;

    }

    void
    ProjectDirectory::closeProject
    ()
    {
        mPath = "";
        if (mProject)
        {
            delete mProject;
            mProject = nullptr;
        }

    }

    string
    ProjectDirectory::findProjectFileInDirectory
    (Directory* dir)
    const
    {
        vector<string> directoryContents;
        directoryContents = dir->list();

        string projectFileName;

        for (const string &filename : directoryContents)
        {
            size_t dotJsonIndex = filename.find(Constants::PROJECT_EXTENSION);
            if (dotJsonIndex != string::npos)
            {
                projectFileName = filename.substr(0,dotJsonIndex);
                LOG_DEBUG( "ProjectDirectory: Found project file ",projectFileName );
                return projectFileName;
            }
        }
        return "";
    }

    bool
    ProjectDirectory::directoryContainsProject
    (Directory* dir)
    const
    {
        bool hasJsonFile = !findProjectFileInDirectory(dir).empty();
        bool hasAssetDirectories = findAssetDirectories(dir);
        return hasJsonFile || hasAssetDirectories;
    }

    bool
    ProjectDirectory::findAssetDirectories
    (Directory* dir)
    const
    {
        auto assetTypes = Constants::DREAM_ASSET_TYPES_MAP;
        for (const auto &typePair : assetTypes)
        {
            auto type = typePair.first;
            string assetDirPath = getAssetTypeDirectory(type,dir->getName());
            Directory* assetDir = mStorageManager->openDirectory(assetDirPath);
            LOG_DEBUG("ProjectDirectory: Checking for {}",assetDir->getPath());
            if (!assetDir->exists())
            {
                mStorageManager->closeDirectory(assetDir);
                assetDir = nullptr;
                return false;
            }
            mStorageManager->closeDirectory(assetDir);
            assetDir = nullptr;
        }
        return true;
    }
}
