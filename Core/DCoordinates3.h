#pragma once

#include <cmath>
#include <GL/glew.h>
#include <iostream>

namespace cagd
{
    //-------------------
    // class DCoordinate3
    //-------------------
    class DCoordinate3
    {
    private:
        GLdouble _data[3];

    public:

        // default constructor
        DCoordinate3();

        // special constructor
        DCoordinate3(GLdouble x, GLdouble y, GLdouble z = 0.0);

        // copy constructor
        DCoordinate3(const DCoordinate3 &other)
        {
            _data[0] = other._data[0];
            _data[1] = other._data[1];
            _data[2] = other._data[2];
        }

        // assignment operator
        DCoordinate3& operator= (const DCoordinate3 &rhs)
                                {
            if( this != &rhs )
            {
                _data[0] = rhs._data[0];
                _data[1] = rhs._data[1];
                _data[2] = rhs._data[2];
            }
            return *this;
        }

        // get components by value
        GLdouble operator [](GLuint index) const;
        GLdouble x() const;
        GLdouble y() const;
        GLdouble z() const;


        // get components by reference
        GLdouble& operator [](GLuint index);
        GLdouble& x();
        GLdouble& y();
        GLdouble& z();

        // change sign
        const DCoordinate3 operator +() const;
        const DCoordinate3 operator -() const;

        // add
        const DCoordinate3 operator +(const DCoordinate3& rhs) const;

        // add to *this
        DCoordinate3& operator +=(const DCoordinate3& rhs);

        // subtract
        const DCoordinate3 operator -(const DCoordinate3& rhs) const;

        // subtract from *this
        DCoordinate3& operator -=(const DCoordinate3& rhs);

        // cross product
        const DCoordinate3 operator ^(const DCoordinate3& rhs) const;

        // cross product, result is stored by *this
        DCoordinate3& operator ^=(const DCoordinate3& rhs);

        // dot product
        GLdouble operator *(const DCoordinate3& rhs) const;

        // scale
        const DCoordinate3 operator *(const GLdouble& rhs) const;
        const DCoordinate3 operator /(const GLdouble& rhs) const;

        // scale *this
        DCoordinate3& operator *=(const GLdouble& rhs);
        DCoordinate3& operator /=(const GLdouble& rhs);

        // length
        GLdouble length() const;

        // normalize
        DCoordinate3& normalize();

        DCoordinate3& XNormal();
        DCoordinate3& YNormal();
        DCoordinate3& ZNormal();
    };

    //-------------------------------------
    // implementation of class DCoordinate3
    //-------------------------------------

    // default constructor
    inline DCoordinate3::DCoordinate3()
    {
        _data[0] = _data[1] = _data[2] = 0.0;
    }

    // special constructor
    inline DCoordinate3::DCoordinate3(GLdouble x, GLdouble y, GLdouble z)
    {
        _data[0] = x;
        _data[1] = y;
        _data[2] = z;
    }

    // get components by value
    inline GLdouble DCoordinate3::operator [](GLuint index) const
    {
        return _data[index];
    }

    inline GLdouble DCoordinate3::x() const
    {
        return _data[0];
    }

    inline GLdouble DCoordinate3::y() const
    {
        return _data[1];
    }

    inline GLdouble DCoordinate3::z() const
    {
        return _data[2];
    }

    // get components by reference
    inline GLdouble& DCoordinate3::operator [](GLuint index)
    {
        return _data[index];
    }

    inline GLdouble& DCoordinate3::x()
    {
        return _data[0];
    }

    inline GLdouble& DCoordinate3::y()
    {
        return _data[1];
    }

    inline GLdouble& DCoordinate3::z()
    {
        return _data[2];
    }

    // change sign
    inline const DCoordinate3 DCoordinate3::operator +() const
    {
        return DCoordinate3(_data[0], _data[1], _data[2]);
    }

    inline const DCoordinate3 DCoordinate3::operator -() const
    {
        return DCoordinate3(-_data[0], -_data[1], -_data[2]);
    }

    // add
    inline const DCoordinate3 DCoordinate3::operator +(const DCoordinate3& rhs) const
    {
        return DCoordinate3(_data[0] + rhs._data[0], _data[1] + rhs._data[1], _data[2] + rhs._data[2]);
    }

    // add to *this
    inline DCoordinate3& DCoordinate3::operator +=(const DCoordinate3& rhs)
    {
        _data[0] += rhs._data[0];
        _data[1] += rhs._data[1];
        _data[2] += rhs._data[2];
        return *this;
    }

    // subtract
    inline const DCoordinate3 DCoordinate3::operator -(const DCoordinate3& rhs) const
    {
        return DCoordinate3(_data[0] - rhs._data[0], _data[1] - rhs._data[1], _data[2] - rhs._data[2]);
    }

    // subtract from *this
    inline DCoordinate3& DCoordinate3::operator -=(const DCoordinate3& rhs)
    {
        _data[0] -= rhs._data[0];
        _data[1] -= rhs._data[1];
        _data[2] -= rhs._data[2];
        return *this;
    }

    // cross product
    inline const DCoordinate3 DCoordinate3::operator ^(const DCoordinate3& rhs) const
    {
        return DCoordinate3(
                _data[1] * rhs._data[2] - _data[2] * rhs._data[1],
                _data[2] * rhs._data[0] - _data[0] * rhs._data[2],
                _data[0] * rhs._data[1] - _data[1] * rhs._data[0]);
    }

    // cross product, result is stored by *this
    inline DCoordinate3& DCoordinate3::operator ^=(const DCoordinate3& rhs)
    {
        GLdouble t1, t2;
        t1 = _data[2] * rhs._data[0] - _data[0] * rhs._data[2];
        t2 = _data[0] * rhs._data[1] - _data[1] * rhs._data[0];
        _data[0] = _data[1] * rhs._data[2] - _data[2] * rhs._data[1];
        _data[1] = t1;
        _data[2] = t2;
        return *this;
    }

    // dot product
    inline GLdouble DCoordinate3::operator *(const DCoordinate3& rhs) const
    {
        return _data[0] * rhs._data[0] + _data[1] * rhs._data[1] + _data[2] * rhs._data[2];
    }

    // scale
    inline const DCoordinate3 DCoordinate3::operator *(const GLdouble& rhs) const
    {
        return DCoordinate3(_data[0] * rhs, _data[1] * rhs, _data[2] * rhs);
    }

    inline const DCoordinate3 operator *(const GLdouble& lhs, const DCoordinate3& rhs)
    {
        return DCoordinate3(lhs * rhs.x(), lhs * rhs.y(), lhs * rhs.z());
    }

    inline const DCoordinate3 DCoordinate3::operator /(const GLdouble& rhs) const
    {
        return DCoordinate3(_data[0] / rhs, _data[1] / rhs, _data[2] / rhs);
    }

    // scale *this
    inline DCoordinate3& DCoordinate3::operator *=(const GLdouble& rhs)
    {
        _data[0] *= rhs;
        _data[1] *= rhs;
        _data[2] *= rhs;

        return *this;
    }

    inline DCoordinate3& DCoordinate3::operator /=(const GLdouble& rhs)
    {
        _data[0] /= rhs;
        _data[1] /= rhs;
        _data[2] /= rhs;

        return *this;
    }

    // length
    inline GLdouble DCoordinate3::length() const
    {
        return std::sqrt((*this) * (*this));
    }

    // normalize
    inline DCoordinate3& DCoordinate3::normalize()
    {
        GLdouble l = length();

        if (l && l != 1.0)
            *this /= l;

        return *this;
    }

    inline DCoordinate3& DCoordinate3::XNormal()
    {
        _data[0] = 1.0;
        _data[1] = 0.0;
        _data[2] = 0.0;

        return *this;
    }

    inline DCoordinate3& DCoordinate3::YNormal()
    {
        _data[0] = 0.0;
        _data[1] = 1.0;
        _data[2] = 0.0;

        return *this;
    }

    inline DCoordinate3& DCoordinate3::ZNormal()
    {
        _data[0] = 0.0;
        _data[1] = 0.0;
        _data[2] = 1.0;

        return *this;
    }

    //----------------------------------------------------------------
    // definitions of overloaded input/output from/to stream operators
    //----------------------------------------------------------------

    // output to stream
    inline std::ostream& operator <<(std::ostream& lhs, const DCoordinate3& rhs)
    {
        return lhs << rhs[0] << " " << rhs[1] << " " << rhs[2];
    }

    // input from stream
    inline std::istream& operator >>(std::istream& lhs, DCoordinate3& rhs)
    {
        return lhs >> rhs[0] >> rhs[1] >> rhs[2];
    }
}
