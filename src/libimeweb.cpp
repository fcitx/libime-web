#include "config.h"

#include "libimeweb.h"

#include <memory>
#include <Cutelyst/Plugins/View/JSON/viewjson.h>
#include <Cutelyst/Plugins/StaticSimple/staticsimple.h>
#include <libime/core/userlanguagemodel.h>
#include <libime/pinyin/pinyindictionary.h>

#include "root.h"

using namespace Cutelyst;

LibIMEWeb::LibIMEWeb(QObject *parent) : Application(parent), ime_(
        std::make_unique<libime::PinyinDictionary>(),
        std::make_unique<libime::UserLanguageModel>(
            libime::DefaultLanguageModelResolver::instance()
                .languageModelFileForLanguage("zh_CN")))
{
    ime_.dict()->load(libime::PinyinDictionary::SystemDict,
                       LIBIME_INSTALL_PKGDATADIR "/sc.dict",
                       libime::PinyinDictFormat::Binary);
}

LibIMEWeb::~LibIMEWeb()
{
}

bool LibIMEWeb::init()
{
    new Root(this);

    new StaticSimple(this);
    new ViewJson(this);

    return true;
}

