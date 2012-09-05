#ifndef ANDROIDRESOURCEPROVIDER_H
#define ANDROIDRESOURCEPROVIDER_H

#include <CEGUI/Base.h>
#include <CEGUI/Exceptions.h>
#include <CEGUI/ResourceProvider.h>
#include <map>
#include <android/asset_manager.h>
#include <vector>
using namespace CEGUI;

class AndroidResourceProvider : public ResourceProvider
{
public:
    AndroidResourceProvider(AAssetManager *assetManager) : d_assetManager(assetManager) {}
    ~AndroidResourceProvider(void) {}
    
    /*!
    \brief
        Set the directory associated with a given resource group identifier.

    \param resourceGroup
        The resource group identifier whose directory is to be set.

    \param directory
        The directory to be associated with resource group identifier
        \a resourceGroup

    \return
        Nothing.
    */
    void setResourceGroupDirectory(const String& resourceGroup, const String& directory);

    /*!
    \brief
        Return the directory associated with the specified resource group
        identifier.

    \param resourceGroup
        The resource group identifier for which the associated directory is to
        be returned.

    \return
        String object describing the directory currently associated with resource
        group identifier \a resourceGroup.

    \note
        This member is not defined as being const because it may cause
        creation of an 'empty' directory specification for the resourceGroup
        if the resourceGroup has not previously been accessed.
    */
    const String& getResourceGroupDirectory(const String& resourceGroup);

    /*!
    \brief
        clears any currently set directory for the specified resource group
        identifier.

    \param resourceGroup
        The resource group identifier for which the associated directory is to
        be cleared.
    */
    void clearResourceGroupDirectory(const String& resourceGroup);

    void loadRawDataContainer(const String& filename, RawDataContainer& output, const String& resourceGroup);
    void unloadRawDataContainer(RawDataContainer& data);
    size_t getResourceGroupFileNames(std::vector<String>& out_vec,
                                     const String& file_pattern,
                                     const String& resource_group);

protected:
    /*!
    \brief
        Return the final path and filename, taking into account the given
        resource group identifier that should be used when attempting to
        load the data.
    */
    String getFinalFilename(const String& filename, const String& resourceGroup) const;

    AAssetManager* d_assetManager;
    
    typedef std::map<String, String, StringFastLessCompare> ResourceGroupMap;
    ResourceGroupMap    d_resourceGroups;
    
};



#endif // ANDROIDRESOURCEPROVIDER_H
