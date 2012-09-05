#include "AndroidResourceProvider.h"
#include "Log.h"

void AndroidResourceProvider::setResourceGroupDirectory(const String &resourceGroup, const String &directory)
{
    
    if (directory.length() == 0)
        return;
    
    LOGI("++++++++++++++++++++++++++++++++++++++");
    LOGI("Directory name: %s", directory.c_str());
    LOGI("++++++++++++++++++++++++++++++++++++++");
    d_resourceGroups[resourceGroup] = directory;
}

const String &AndroidResourceProvider::getResourceGroupDirectory(const String &resourceGroup)
{
    LOGI("++++++++++++++++++++++++++++++++++++++");
    LOGI("Directory name: %s", resourceGroup.c_str());
    LOGI("++++++++++++++++++++++++++++++++++++++");
    
    return d_resourceGroups[resourceGroup];
}

void AndroidResourceProvider::clearResourceGroupDirectory(const String &resourceGroup)
{
    ResourceGroupMap::iterator iter = d_resourceGroups.find(resourceGroup);

    if (iter != d_resourceGroups.end())
        d_resourceGroups.erase(iter);
}

void AndroidResourceProvider::loadRawDataContainer(const String &filename, RawDataContainer &output, const String &resourceGroup)
{
    if (filename.empty())
        CEGUI_THROW(InvalidRequestException(
            "Filename supplied for data loading must be valid"));

    const String final_filename(getFinalFilename(filename, resourceGroup));

    AAsset* asset = AAssetManager_open(d_assetManager, final_filename.c_str(), AASSET_MODE_BUFFER);

    
    
    if (asset == 0)
        CEGUI_THROW(FileIOException(final_filename + " does not exist"));

    
    const size_t size = AAsset_getLength(asset);
    

    unsigned char* const buffer = CEGUI_NEW_ARRAY_PT(unsigned char, size, RawDataContainer);

    
    
    const size_t size_read = AAsset_read(asset, buffer, size);

    AAsset_close(asset);

    if (size_read != size)
    {
        CEGUI_DELETE_ARRAY_PT(buffer, unsigned char, size, BufferAllocator);

        CEGUI_THROW(FileIOException(
            "A problem occurred while reading file: " + final_filename));
    }

    output.setData(buffer);
    output.setSize(size);
    
}

void AndroidResourceProvider::unloadRawDataContainer(RawDataContainer &data)
{
    data.release();
}

size_t AndroidResourceProvider::getResourceGroupFileNames(std::vector<String> &out_vec, const String &file_pattern, const String &resource_group)
{
    
    // look-up resource group name
    ResourceGroupMap::const_iterator iter =
        d_resourceGroups.find(resource_group.empty() ? d_defaultResourceGroup :
                              resource_group);
    // get directory that's set for the resource group
    const String dir_name(
        iter != d_resourceGroups.end() ? (*iter).second : "./");

    size_t entries = 0;


   AAssetDir* directory = AAssetManager_openDir(d_assetManager, dir_name.c_str());
   
   const char* filename;
   do {
     
       filename = AAssetDir_getNextFileName(directory);
       out_vec.push_back(filename);
       ++entries;
       
   } while (filename != NULL);
    
  
    AAssetDir_close(directory);

    return entries;
}

String AndroidResourceProvider::getFinalFilename(const String &filename, const String &resourceGroup) const
{
    String final_filename;

    // look up resource group directory
    ResourceGroupMap::const_iterator iter =
        d_resourceGroups.find(resourceGroup.empty() ?
            d_defaultResourceGroup :
            resourceGroup);

    // if there was an entry for this group, use it's directory as the
    // first part of the filename
    if (iter != d_resourceGroups.end())
        final_filename = (*iter).second;

    // append the filename part that we were passed
    final_filename += filename;

    // return result
    return final_filename;
}
