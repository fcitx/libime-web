#ifndef LIBIMEWEB_H
#define LIBIMEWEB_H

#include <Cutelyst/Application>
#include <libime/pinyin/pinyinime.h>

using namespace Cutelyst;

class LibIMEWeb : public Application
{
    Q_OBJECT
    CUTELYST_APPLICATION(IID "LibIMEWeb")
public:
    Q_INVOKABLE explicit LibIMEWeb(QObject *parent = 0);
    ~LibIMEWeb();

    bool init();

    libime::PinyinIME &ime() { return ime_; }

private:
    libime::PinyinIME ime_;

};

#endif //LIBIMEWEB_H

