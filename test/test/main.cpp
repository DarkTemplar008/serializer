#include <QCoreApplication>
#include <QDebug>
#include "serializer/serializer.hpp"

namespace sys {
struct Subject
{
    int id;
    std::string obj_name;
    std::string ref;
};

struct Student
{
    int id;
    std::string name;
    std::vector<Subject> sub_vec;
};

}

QJSON_SERIAILIZER_BEGIN(sys::Subject)
    QJSON_SERIALIZER_MEMBER(id)
    QJSON_SERIALIZER_MEMBER(obj_name)
    QJSON_SERIALIZER_MEMBER(ref)
QJSON_SERIALIZER_END(sys::Subject)

QJSON_SERIAILIZER_BEGIN(sys::Student)
    QJSON_SERIALIZER_MEMBER(id)
    QJSON_SERIALIZER_MEMBER(name)
    QJSON_SERIALIZER_MEMBER(sub_vec)
QJSON_SERIALIZER_END(sys::Student)

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    sys::Student student = {2, "shelei", {{1, "language", "good"},{2, "english", "bad"}}};
    std::string value;
    serializer::qjson::serialize(student, value);

    qDebug() << value.c_str() ;

    return a.exec();
}
