#include <dlfcn.h>
#include <link.h>
#include <span>
#include <string>
#include "main.h"
#include <libhat.hpp>

extern "C" [[gnu::visibility("default")]] void mod_preinit() {}
extern "C" [[gnu::visibility("default")]] void mod_init()
{
    void *mcLib = dlopen("libminecraftpe.so", 0);
    if (!mcLib)
    {
        printf("[ShulkerPreview] failed to open libminecraftpe.so\n");
        return;
    }

    std::span<std::byte> range1, range2;
    auto callback = [&](const dl_phdr_info &info)
    {
        if (auto h = dlopen(info.dlpi_name, RTLD_NOLOAD); dlclose(h), h != mcLib)
            return 0;
        range1 = {reinterpret_cast<std::byte *>(info.dlpi_addr + info.dlpi_phdr[1].p_vaddr), info.dlpi_phdr[1].p_memsz};
        range2 = {reinterpret_cast<std::byte *>(info.dlpi_addr + info.dlpi_phdr[2].p_vaddr), info.dlpi_phdr[2].p_memsz};
        return 1;
    };
    dl_iterate_phdr([](dl_phdr_info *info, size_t, void *data)
                    { return (*static_cast<decltype(callback) *>(data))(*info); }, &callback);

    // ShulkerBoxBlockItem
    auto ZTS19ShulkerBoxBlockItem = hat::find_pattern(range1, hat::object_to_signature("19ShulkerBoxBlockItem")).get();
    auto _ZTI19ShulkerBoxBlockItem = hat::find_pattern(range2, hat::object_to_signature(ZTS19ShulkerBoxBlockItem)).get() - sizeof(void *);
    auto _ZTV19ShulkerBoxBlockItem = hat::find_pattern(range2, hat::object_to_signature(_ZTI19ShulkerBoxBlockItem)).get() + sizeof(void *);
    void **vtshulk53 = reinterpret_cast<void **>(_ZTV19ShulkerBoxBlockItem);
    // append slot 53
    ShulkerBoxBlockItem_appendFormattedHovertext_orig =
        reinterpret_cast<Shulker_appendHover_t>(vtshulk53[53]);
    vtshulk53[53] = reinterpret_cast<void *>(&ShulkerBoxBlockItem_appendFormattedHovertext_hook);

    //was itemstackbase here

    //HovertextRenderer
    auto _ZTS17HoverTextRenderer = hat::find_pattern(range1, hat::object_to_signature("17HoverTextRenderer")).get();
    auto _ZTI17HoverTextRenderer = hat::find_pattern(range2, hat::object_to_signature(_ZTS17HoverTextRenderer)).get() - sizeof(void *);
    auto _ZTV17HoverTextRenderer = hat::find_pattern(range2, hat::object_to_signature(_ZTI17HoverTextRenderer)).get() + sizeof(void *);
    //slot17
    void **vtHR = reinterpret_cast<void **>(_ZTV17HoverTextRenderer);
    HoverRenderer_renderHoverBox_orig = 
        reinterpret_cast<RenderHoverBoxFn>(vtHR[17]);
    vtHR[17] = reinterpret_cast<void *>(&HoverRenderer_renderHoverBox_hook);

    // //itemrelated//
    // auto itemstr = hat::find_pattern(range1, hat::object_to_signature("4Item")).get();
    // auto itemtyp = hat::find_pattern(range2, hat::object_to_signature(itemstr)).get() - sizeof(void *);
    // auto itemvtb = hat::find_pattern(range2, hat::object_to_signature(itemtyp)).get() + sizeof(void *);
    // //slot 53
    // void **vti = reinterpret_cast<void **>(itemvtb);
    // Item_getMaxDamage_orig = 
    //     reinterpret_cast<Item_getMaxDamage_t>(vti[53]);
    // vti[36] = reinterpret_cast<void *>(&Item_getMaxDamage_hook);

    auto witemstr = hat::find_pattern(range1, hat::object_to_signature("10WeaponItem")).get();
    auto witemtyp = hat::find_pattern(range2, hat::object_to_signature(witemstr)).get() - sizeof(void *);
    auto witemvtb = hat::find_pattern(range2, hat::object_to_signature(witemtyp)).get() + sizeof(void *);
    void **vtw = reinterpret_cast<void **>(witemvtb);
    WeaponItem_appendFormattedHovertext_orig = 
        reinterpret_cast<Weapon_appendHover_t>(vtw[53]);
    vtw[53] = reinterpret_cast<void *>(&WeaponItem_appendFormattedHovertext_hook);
    //this is really ugly Dx
    //pickaxeitem
    auto pitemstr = hat::find_pattern(range1, hat::object_to_signature("11PickaxeItem")).get();
    auto pitemtyp = hat::find_pattern(range2, hat::object_to_signature(pitemstr)).get() - sizeof(void *);
    auto pitemvtb = hat::find_pattern(range2, hat::object_to_signature(pitemtyp)).get() + sizeof(void *);
    void **vtp = reinterpret_cast<void **>(pitemvtb);
}