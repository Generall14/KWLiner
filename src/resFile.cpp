#include "resFile.hpp"
#include "QFile"
#include "QTextStream"

ResFile::ResFile(QString name, uint light, uint comment, uint code):
    _name(name),
    _total(light+comment+code),
    _light(light),
    _comment(comment),
    _code(code)
{

}

ResFile::ResFile():
    ResFile("", 0, 0, 0)
{

}

ResFile ResFile::ParseFile(QString fileAdr, const Set *set) throw(std::runtime_error)
{
    QFile file(fileAdr);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw std::runtime_error(QString("ResFile::ParseFile: nie można otworzyć pliku "+fileAdr).toStdString());

    QString name = file.fileName().split("/").last();
    uint code = 0, light = 0, comment = 0;

    QTextStream ts(&file);

    // Paskudny kawał kodu, działa to nie ruszać!!!:
    QString waitingEnding = "";
    while(!ts.atEnd())
    {
        QString line = ts.readLine();
        bool someComment = false;
        bool done = false;

        while(!done)
        {
            bool needCnt = false;
            if(!waitingEnding.isEmpty())
            {
                someComment = true;
                if(line.indexOf(waitingEnding)>=0)
                {
                    line = line.remove(0, line.indexOf(waitingEnding)+waitingEnding.size());
                    waitingEnding = "";
                }
                else
                {
                    line = "";
                    done = true;
                }
                continue;
            }

            // rozeznanie (który rodzaj komentarza wystąpił pierwszy):
            int firstsimple = 0xFFFF;
            for(auto sig: set->GetOneLineComments())
            {
                int fi = line.indexOf(sig);
                if(fi>=0)
                {
                    if(fi<firstsimple)
                        firstsimple = fi;
                }
            }
            int firstdouble = 0xFFFF;
            for(QPair<QString, QString> pair: set->GetStartEndComments())
            {
                int fi = line.indexOf(pair.first);
                if(fi>=0)
                {
                    if(fi<firstdouble)
                        firstdouble = fi;
                }
            }


            if((firstdouble!=0xFFFF) && ((firstsimple==0xFFFF)||(firstdouble<firstsimple)))
            {
                for(QPair<QString, QString> pair: set->GetStartEndComments())
                {
                    int fi = line.indexOf(pair.first);
                    if(fi>=0)
                    {
                        int sec = line.indexOf(pair.second, fi);
                        if(sec>=0)
                        {
                            line = line.remove(fi, sec-fi+pair.second.size());
                            someComment = true;
                            needCnt = true;
                            break;
                        }
                        else
                        {
                            waitingEnding = pair.second;
                            line = line.left(fi);
                            done = true;
                            break;
                        }
                    }
                }
            }
            else if((firstsimple!=0xFFFF) && ((firstdouble==0xFFFF)||(firstsimple<firstdouble)))
            {
                line = line.left(firstsimple);
                someComment = true;
                done = true;
                break;
            }

            if(needCnt)
                continue;


            done = true;
        }


        if(!line.isEmpty())
            code++;
        else
        {
            if(someComment)
                comment++;
            else
                light++;
        }
    }

    file.close();
    return ResFile(name, light, comment, code);
}

QString ResFile::Name() const
{
    return _name;
}

uint ResFile::Total() const
{
    return _total;
}

uint ResFile::Light() const
{
    return _light;
}

uint ResFile::Comment() const
{
    return _comment;
}

uint ResFile::Code() const
{
    return _code;
}

QString ResFile::toString() const
{
    QString temp = _name+", ";
    temp.append(" total: " + QString::number(_total));
    temp.append(" code: " + QString::number(_code));
    temp.append(" comment: " + QString::number(_comment));
    temp.append(" light: " + QString::number(_light));
    return temp;
}
