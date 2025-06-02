#ifndef CONTACTO_HPP
#define CONTACTO_HPP

template <typename T>
struct Contacto{
public:
    T nombre;
    T telefono;
    T correo;

    Contacto()=default;
    Contacto(T n, T t, T c): nombre(n), telefono(t), correo(c){}


    bool operator<(const Contacto& otro)const{
        return nombre<otro.nombre;
    }

    bool operator==(const Contacto& otro)const{
        return nombre == otro.nombre;
    }

    void mostrar()const {
        std::cout<<"Nombre: "<<nombre<<"\n"
                <<"Telefono: "<<telefono<<"\n"
                <<"Correo: "<<correo<<"\n";
    }
};
#endif // CONTACTO_HPP
