#ifndef KROJNALISTA
#define KROJNALISTA

#include <vector>
#include <iostream>
#include <algorithm>
#include <QString>
#include <unistd.h>
//#define DEBUG

class krojnaLista
{
public:
    krojnaLista(int min,int max,int duzina,int sirina,std::vector<int> & e)
        : minOtpad(min) , maxOtpad(max) , duzinaSipke(duzina) , sirinaReza(sirina) ,niz(e)
    {}

    void racunaj()
    {
#ifdef DEBUG
        //std::cout << "Size:" << niz.size() << std::endl;
        std::cout << std::endl << "Sleep" << std::endl << std::endl;
        //sleep(1);
#endif
        //std::sort(niz.begin(),niz.end(),std::greater<int>());

        if(niz[0] >= duzinaSipke)
        {
            greska="Element longer than lenght!";
            return;
        }
        if(maxOtpad < minOtpad)
        {
            //greska="MaxOtpad ne sme biti manji od MinOtpad!";
            greska="Min of Rest should be larger then Max of trash!";
            return;
        }

        if(maxOtpad >= duzinaSipke)
        {
            //greska="MaxOtpad ne sme biti veci od duzine Sipke";
            greska="Min of trash needs to be smaller than Length of Item!";
            return;
        }

        if(niz[0]==0)
        {
            greska="Element should not be 0!";
            return;
        }
#ifdef DEBUG
        for(unsigned int i=0;i<niz.size();i++)
            std::cout << niz[i] << " ";
        std::cout << std::endl;
#endif

        if(listaMin(0,duzinaSipke) == false)
            rest(duzinaSipke);

#ifdef DEBUG
        std::cout << ispis().toStdString() << std::endl;
#endif

        std::sort(niz.begin(),niz.end(),std::greater<int>());

#ifdef DEBUG
        //while(niz.size()>0 && niz[niz.size()-1]==0)
            //niz.pop_back();

       /* for(unsigned int i=0;i<niz.size();i++)
            std::cout << niz[i] << " ";
        std::cout << std::endl;*/
#endif


        return;
    }

    bool error()
    {
        if(!greska.empty())
            return true;
        return false;
    }

    std::string stanje()
    {
        return greska;
    }

    void rest(int left)
    {

        unsigned int index=0;


        if(niz[0] > left-maxOtpad)
        {
            greska="An Element has wrong size!";
            return;
        }

        if(niz[0] <= 0)
        {
            greska="An Element is in wrong state!";
            return;
        }

        left = left - niz[0];
        rez.push_back(niz[0]);
        niz[0] = 0;
        index++;

        while(niz[index]!=0)
        {
            if(left-sirinaReza-niz[index] <= maxOtpad)
            {
                index++;
                continue;
            }
            left=left - niz[index] - sirinaReza;
            rez.push_back(niz[index]);
            niz[index]=0;
            index++;
        }

        return;
    }

    QString ispis()
    {
        int sum=0;
        QString text;
        for(unsigned int i=0;i<rez.size();i++)
        {
            text.append(QString("%1").arg(rez[i]));
            if(i+1<rez.size())
            {
                text.append(" | ");
                sum+=rez[i]+sirinaReza;
            }
            else
            {
                text.append(" -> ");
                sum+=rez[i];
            }
        }
        text.append(QString("%1").arg(sum));
        return text;
    }


    bool listaMin(unsigned int index,int left)
    {

        if(left+sirinaReza <= minOtpad  && left+sirinaReza >= 0)
            return true;
        if(index >= niz.size() || niz[index]==0)
            return false;


        while(niz[index]!=0)
        {
            if(niz[index] < left)
            {
                int tmp=niz[index];
                if(listaMin(index+1,left-tmp-sirinaReza))
                {
                    rez.push_back(niz[index]);
                    niz[index]=0;
                    return true;
                }


                index++;
                while(index < niz.size() && niz[index-1]==niz[index])
                    index++;
            }
            else
                index++;
        }
        return false;
    }


private:
    int minOtpad;
    int maxOtpad;
    int duzinaSipke;
    int sirinaReza;
    std::string greska="";
    std::vector<int> & niz;

    std::vector<int> rez;
};

#endif // KROJNALISTA

