#include <iostream>

class KomleksanBroj {
public:
    KomleksanBroj() :
        m_re(0.0), m_im(0.0) {
        // std::cout << "Kreiran" << std::endl;
    }

    KomleksanBroj(double re, double im)
        : m_re(re), m_im(im) {
        // std::cout << "Kreiran" << std::endl;
    }

    ~KomleksanBroj() {
        // std::cout << "Unisten" << std::endl;
    }
        
    double get_re() const {
        return m_re;
    }

    double get_im() const {
        return m_im;
    }

    void set_re(double re) {
        m_re = re;
    }

    void set_im(double im) {
        m_im = im;
    }

    KomleksanBroj operator+(const KomleksanBroj& drugi) const {
        return KomleksanBroj(
            get_re() + drugi.get_re(),
            get_im() + drugi.get_im()
        );
    }

    KomleksanBroj operator-(const KomleksanBroj& drugi) const {
        return KomleksanBroj(
            get_re() - drugi.get_re(),
            get_im() - drugi.get_im()
        );
    }

    KomleksanBroj& operator+=(const KomleksanBroj& drugi) {
        m_re += drugi.m_re;
        m_im += drugi.m_im;

        return *this;
    }

    KomleksanBroj& operator-=(const KomleksanBroj& drugi) {
        m_re -= drugi.m_re;
        m_im -= drugi.m_im;

        return *this;
    }

    KomleksanBroj& operator++() {
        m_re++;
        return *this;
    }

    KomleksanBroj operator++(int) {
        KomleksanBroj kb = *this;
        m_re++;
        return kb;
    }

private:
    double m_re, m_im;
};

std::ostream& operator<<(std::ostream& os, const KomleksanBroj& kb) {
    os << kb.get_re() << " + " << kb.get_im() << " * i";
    return os;
}

std::istream& operator>>(std::istream& is, KomleksanBroj& kb) {
    double re, im;
    is >> re >> im;

    kb.set_re(re);
    kb.set_im(im);

    return is;
}

int main() {
    const KomleksanBroj z(1, 2);
    std::cout << z.get_re() << std::endl;

    return 0;
}