#include "root.h"
#include "libimeweb.h"
#include <libime/pinyin/pinyincontext.h>
#include <libime/pinyin/shuangpinprofile.h>
#include <algorithm>

using namespace Cutelyst;

Root::Root(QObject *parent) : Controller(parent)
{
}

Root::~Root()
{
}

void Root::index(Context *c)
{
    c->response()->body() = "Welcome to LibIMEWeb, use url like /pinyin?py=[py][&sp=[shuangpin profile]] to type! E.g. /pinyin?py=nalingvkdk&sp=ziranma or /pinyin?py=nihao";
}

bool decodeSpProfile(const QString &sp, libime::ShuangpinBuiltinProfile *profile) {
    if (sp == "ziranma") {
        *profile = libime::ShuangpinBuiltinProfile::Ziranma;
        return true;
    } else if (sp == "ms") {
        *profile = libime::ShuangpinBuiltinProfile::MS;
        return true;
    } else if (sp == "abc") {
        *profile = libime::ShuangpinBuiltinProfile::ABC;
        return true;
    } else if (sp == "zhongwenzhixing") {
        *profile = libime::ShuangpinBuiltinProfile::Zhongwenzhixing;
        return true;
    } else if (sp == "pinyinjiajia") {
        *profile = libime::ShuangpinBuiltinProfile::PinyinJiajia;
        return true;
    } else if (sp == "xiaohe") {
        *profile = libime::ShuangpinBuiltinProfile::Xiaohe;
        return true;
    }
    return false;
}

void Root::pinyin(Context *c)
{
    auto app = static_cast<LibIMEWeb *>(c->app());
    libime::PinyinContext context(&app->ime());
    auto py = c->request()->param("py");
    auto sp = c->request()->param("sp");

    libime::ShuangpinBuiltinProfile profile;
    if (decodeSpProfile(sp, &profile)) {
        app->ime().setShuangpinProfile(std::make_shared<libime::ShuangpinProfile>(profile));
        context.setUseShuangpin(true);
    }

    if (!std::all_of(py.begin(), py.end(), [&context, app](const QChar &chr) {
        char c = chr.toLatin1();
        return (c >= 'a' && c <= 'z') || c == '\'' || (
        context.useShuangpin() && app->ime().shuangpinProfile()->validInput().count(c));
    })) {
        return;
    }
    auto bytes = py.toLatin1();
    context.type(bytes.constData(), bytes.size());
    context.setMaxSize(30);
    if (context.candidates().size()) {
        QString py = QString::fromStdString(context.candidateFullPinyin(0));
        QString hanzi = QString::fromStdString(context.sentence());
        c->setStash("full_pinyin", py);
        c->setStash("hanzi", hanzi);
    }
}

void Root::defaultPage(Context *c)
{
    c->response()->body() = "Page not found!";
    c->response()->setStatus(404);
}

