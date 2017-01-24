#ifndef DEO
#define DEO



class Deo
{
public:

    Deo(int d,int k)
        : _duzina(d) , _kolicina(k)
    {}

    void duzina(int d)
    {
        _duzina=d;
    }

    void kolicina(int k)
    {
        _kolicina=k;
    }

    int duzina()
    {
        return _duzina;
    }

    int kolicina()
    {
        return _kolicina;
    }

    void kolicina(int k,char c)
    {
        if(c=='+')
            _kolicina+=k;
        else if(c=='-')
            _kolicina-=k;
    }

private:
    int _duzina;
    int _kolicina;
};

#endif // DEO

