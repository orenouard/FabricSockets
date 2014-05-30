/*
 *  Copyright 2010-2014 Fabric Software Inc. All rights reserved.
 */

#ifndef __handle_h__
#define __handle_h__

template <class T>
struct Handle
{
private:
  T * m_data;
  bool m_owned;
  Fabric::EDK::AtomicUInt32 m_refCount;

public:
  Handle(T * data, bool owned = false)
  {
    Fabric::EDK::AtomicUInt32SetValue( 1, &m_refCount );
    m_data = data;
    m_owned = owned;
  }

  void retain()
  {
    Fabric::EDK::AtomicUInt32Increment( &m_refCount );
  }

  void release()
  {
    if ( Fabric::EDK::AtomicUInt32DecrementAndGetValue( &m_refCount ) == 0 )
    {
      if(m_data != NULL && m_owned)
        delete(m_data);

      delete this;
    }
  }

  T * data()
  {
    return m_data;
  }

  const T * data() const
  {
    return m_data;
  }

};

#endif
