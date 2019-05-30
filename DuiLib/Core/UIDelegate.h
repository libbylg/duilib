#ifndef __UIDELEGATE_H__
#define __UIDELEGATE_H__

#include "Core/UIDefine.h"

namespace DUILIB
{

    class DUILIB_API CDelegateBase
    {
    public:
        CDelegateBase(void* pObject, void* pFn);
        CDelegateBase(const CDelegateBase& rhs);
        virtual ~CDelegateBase();
        BOOL Equals(const CDelegateBase& rhs) const;
        BOOL operator() (void* param);
        virtual CDelegateBase* Copy() const = 0; // add const for gcc

    protected:
        void* GetFn();
        void* GetObject();
        virtual BOOL Invoke(void* param) = 0;

    private:
        void* m_pObject;
        void* m_pFn;
    };

    class CDelegateStatic : public CDelegateBase
    {
        typedef BOOL (*Fn)(void*);
    public:
        CDelegateStatic(Fn pFn) : CDelegateBase(NULL, pFn) {}
        CDelegateStatic(const CDelegateStatic& rhs) : CDelegateBase(rhs) {}
        virtual CDelegateBase* Copy() const { return new CDelegateStatic(*this); }

    protected:
        virtual BOOL Invoke(void* param)
        {
            Fn pFn = (Fn)GetFn();
            return (*pFn)(param);
        }
    };

    template <class O, class T>
    class CDelegate : public CDelegateBase
    {
        typedef BOOL (T::* Fn)(void*);
    public:
        CDelegate(O* pObj, Fn pFn) : CDelegateBase(pObj, *(void**)& pFn) {}
        CDelegate(const CDelegate& rhs) : CDelegateBase(rhs) {}
        virtual CDelegateBase* Copy() const { return new CDelegate(*this); }

    protected:
        virtual BOOL Invoke(void* param)
        {
            O* pObject = (O*)GetObject();
            union
            {
                void* ptr;
                Fn fn;
            } func = {GetFn()};
            return (pObject->*func.fn)(param);
        }

    private:
        Fn m_pFn;
    };

    template <class O, class T>
    CDelegate<O, T> MakeDelegate(O* pObject, BOOL (T::* pFn)(void*))
    {
        return CDelegate<O, T>(pObject, pFn);
    }

    inline CDelegateStatic MakeDelegate(BOOL (*pFn)(void*))
    {
        return CDelegateStatic(pFn);
    }

    class DUILIB_API CEventSource
    {
        typedef BOOL (*FnType)(void*);
    public:
        ~CEventSource();
        operator BOOL();
        void operator+= (const CDelegateBase& d); // add const for gcc
        void operator+= (FnType pFn);
        void operator-= (const CDelegateBase& d);
        void operator-= (FnType pFn);
        BOOL operator() (void* param);

    protected:
        CPtrArrayUI m_aDelegates;
    };

} // namespace DUILIB

#endif // __UIDELEGATE_H__