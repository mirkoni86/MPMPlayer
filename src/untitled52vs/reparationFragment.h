#ifndef REPARATIONFRAGMENT_H
#define REPARATIONFRAGMENT_H
class ReparationFragment
{
public:
    ReparationFragment();
    ~ReparationFragment();
    inline void setA(int a)
    {
        m_iA = a;
    }
    inline void setB(int b)
    {
        m_iB = b;
    }
    inline int retA()
    {
        return m_iA;
    }
    inline int retB()
    {
        return m_iB;
    }
    inline void setPlay(int a)
    {
        m_iPlay = a;
    }
    inline int status()
    {
        return m_iPlay;
    }
private:
   int m_iPlay;
   int m_iA;
   int m_iB;
};
#endif // REPARATIONFRAGMENT_H
