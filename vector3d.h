#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <string>
#include <ostream>

typedef double real;
#define tol12 1.e-12

#include <math.h>


struct ErrorAt
{
  std::string filename;
  int line;
  std::string msg;

  ErrorAt( const std::string &aFileName, int aLineNo, const std::string &aMsg = "" )
    : filename( aFileName )
    , line( aLineNo )
    , msg( aMsg )
  {}
};

inline
std::ostream & operator << ( std::ostream &os, const ErrorAt &e )
{
  os << e.filename << ": " << e.line << ": " << e.msg;
  return os;
}


struct tensor3D
{
public:
  tensor3D()
  {
    zero();
  }

  void zero()
  {
    for ( int i = 0; i < 9; ++i )
      b[i] = 0.;
  }

  void unit()
  {
    zero();
    b[0] = 1.;
    b[4] = 1.;
    b[8] = 1.;
  }

//  tensor3D& trn()
//  {
//    tensor3D t_tmp;
//
//    for ( int i = 1, k = 0; i <= DIM; ++i )
//      for ( int j = 1; j <= DIM; ++j, ++k )
//        t_tmp.b[k] = b[ DIM * (j-1) + (i-1) ];
//
//
//    return t_tmp;
//  }


  real  operator()  (int i, int j) const
  {
    if ( i > DIM || i < 1 || j > DIM || j < 1 )
      throw ErrorAt( __FILE__, __LINE__ );

    return b[ DIM * (i-1) + (j-1) ];
  }

  real&  operator()  (int i, int j)
  {
    if ( i > DIM || i < 1 || j > DIM || j < 1 )
      throw ErrorAt( __FILE__, __LINE__ );


    return b[ DIM * (i-1) + (j-1) ];
  }



  tensor3D&  operator+=  (const real& d)
  {
    for ( int k = 0; k < size(); ++k )
      b[k] += d;

    return *this;
  }
  tensor3D&  operator*=  (const real& d)
  {
    for ( int k = 0; k < size(); ++k )
      b[k] *= d;

    return *this;
  }
  tensor3D&  operator-=  (const real& d)
  {
    for ( int k = 0; k < size(); ++k )
      b[k] -= d;

    return *this;
  }
  tensor3D&  operator/= (const real& d)
  {

    real dd = d;
    if (dd == 0) dd = 1e-13;

    for ( int k = 0; k < size(); ++k )
      b[k] /= dd;

    return *this;
  }

  tensor3D  operator+  (const real& d)
  {
    tensor3D t_tmp(*this);
    t_tmp += d;

    return t_tmp;
  }
  tensor3D  operator- (const real& d)
  {
    tensor3D t_tmp(*this);
    t_tmp -= d;

    return t_tmp;
  }
  tensor3D  operator/  (const real& d)
  {
    tensor3D t_tmp(*this);
    t_tmp /= d;

    return t_tmp;
  }

  tensor3D  operator+  (const tensor3D& M)
  {
    tensor3D t_tmp(*this);
    for ( int k = 0; k < DIM * DIM; ++k )
      t_tmp.b[k] += M.b[k];

    return t_tmp;
  }

  tensor3D  operator*  (const tensor3D& M)
  {
    tensor3D t_tmp;

    for ( int i = 0, k = 0; i < DIM; ++i )
      for ( int j = 0; j < DIM; ++j, ++k )
        for ( int c = 0; c < DIM; ++c )
        {
          t_tmp.b[k] += b[DIM * i + c] * M.b[ j + c * DIM ];
//          std::cout<< b[DIM * i + c] << " " <<M.b[ j + c * DIM ]<<" "<<t_tmp.b[k] << std::endl;
        }
    return t_tmp;

  }



private:
  static int size () { return 9; }

  real b[9];
  enum { DIM = 3 };
};


tensor3D  operator*  (const tensor3D &t, const real& d);
tensor3D  operator*  (const real& d, const tensor3D &t);


//tensor3D  operator+  (const real& d, const tensor3D &t)
//{
//  return t+d;
//}
//tensor3D  operator-  (const real& d, const tensor3D &t)
//{
//  return t*(-1.)+d;
//}

struct Vector3D
{

public:

  Vector3D  ()                           { x = 0;      y = 0;      z = 0;      }
  Vector3D  (real xx,real yy,real zz)    { x = xx;     y = yy;     z = zz;     }
  Vector3D  (real*  a)                   { x = a[ 0 ]; y = a[ 1 ]; z = a[ 2 ]; }
  Vector3D  (const Vector3D& src)        { x = src.x;  y = src.y;  z = src.z;  }


//  operator real*() const
//  {
//    return ((real*)this);
//  }

  Vector3D&  operator=  (const Vector3D& p)
  {
    x=p.x; y=p.y; z=p.z;
    return *this;
  }

  real&        operator[] (int i)       { return *((real*)this+i); }
  const real&  operator[] (int i) const { return *((real*)this+i); }

  Vector3D   operator+  (const Vector3D& p) const
  {
    Vector3D p_tmp( x + p.x, y + p.y, z + p.z );
    return p_tmp;
  }

  Vector3D   operator-  (const Vector3D& p) const
  {
    Vector3D p_tmp( x - p.x, y - p.y, z - p.z );
    return p_tmp;
  }

  Vector3D   operator-  () const
  {
    Vector3D p_tmp(-x, -y, -z);
    return p_tmp;
  }

  Vector3D   operator/  (real d) const
  {
    if (d==0) d = tol12;
    Vector3D p_tmp(x/d, y/d, z/d);
    return p_tmp;
  }

  Vector3D   operator*  (real d) const
  {
    Vector3D p_tmp(x*d, y*d, z*d);
    return p_tmp;
  }

  friend Vector3D   operator*  (real d, Vector3D v)
  {
    Vector3D p_tmp(v.x*d, v.y*d, v.z*d);
    return p_tmp;
  }



  Vector3D   operator+= (const Vector3D& p)
  {
    x += p.x;
    y += p.y;
    z += p.z;
    return *this;
  }

  Vector3D   operator-= (const Vector3D& p)
  {
    x -= p.x;
    y -= p.y;
    z -= p.z;
    return *this;
  }

  Vector3D   operator/= (real d)
  {
    if (d==0) d = tol12;
    x /= d;
    y /= d;
    z /= d;
    return *this;
  }

  Vector3D   operator*=  (real d)
  {
    x *= d;
    y *= d;
    z *= d;
    return *this;
  }

  real operator* (const Vector3D& p) const
  {
    real d  = x*p.x + y*p.y + z*p.z;
    return  d;
  }


  real norm() const
  {
    return sqrt( x*x + y*y + z*z );
  }

  friend Vector3D operator *(const Vector3D& v, const tensor3D& t)
  {
    Vector3D p_tmp;

    for ( int i = 0; i < 3; ++i )
      for( int j = 0; j < 3; ++j )
        p_tmp[i] += t(j+1,i+1) * v[j];

    return p_tmp;
  }

  friend Vector3D operator *(const tensor3D& t, const Vector3D& v)
  {
    Vector3D p_tmp;

    for ( int i = 0; i < 3; ++i )
      for( int j = 0; j < 3; ++j )
        p_tmp[i] += t(i+1,j+1) * v[j];

    return p_tmp;
  }

  Vector3D cross (const Vector3D& p) const
  {
    Vector3D ptmp;
    ptmp.x =  y*p.z - z*p.y;
    ptmp.y =  z*p.x - x*p.z;
    ptmp.z =  x*p.y - y*p.x;
    return ptmp;
  }


  real x, y, z;


};

inline Vector3D cross (const Vector3D& p1, const Vector3D& p2)
{
  return p1.cross(p2);
}

inline Vector3D tray(const tensor3D& src)
{
  return Vector3D(src(1,1), src(2,2), src(3,3));
}

inline real sum(const Vector3D& p)
{
  return p.x+p.y+p.z;
}



#endif // VECTOR3D_H
