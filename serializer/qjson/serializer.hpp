#ifndef SERIALIZER_QJSON_SERIALIZER_HPP
#define SERIALIZER_QJSON_SERIALIZER_HPP

#define QJSON_SPACE_BEGIN namespace qjson {
#define QJSON_SPACE_END }

#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

SERIALIZER_SPACE_BEGIN
QJSON_SPACE_BEGIN

template <class T>
struct Serializer
{
    typedef T type;
};

template <class T>
QJsonValue& serialize(const T& value, QJsonValue& js_value)
{
    js_value = QJsonValue(value);
    return js_value;
}

template <>
QJsonValue& serialize(const std::string& str, QJsonValue& js_value)
{
    js_value = QJsonValue(str.c_str());
    return js_value;
}

template <class T>
QJsonValue& serialize(const std::vector<T>& vec, QJsonValue& js_value)
{
    QJsonArray array;
    for (int i = 0; i < vec.size(); ++i)
    {
        QJsonValue sub_value;
        serialize(vec[i], sub_value);
        array.push_back(sub_value);
    }
    js_value = array;
    return js_value;
}

#define QJSON_SERIAILIZER_BEGIN(Cls) namespace serializer { namespace qjson { \
    template <>\
    struct Serializer<Cls> {\
        typedef Cls type;\
        static QJsonValue& serialize_(const Cls& value, QJsonValue& js_value)\
        {\
            QJsonObject js_obj;

#define QJSON_SERIALIZER_MEMBER(Field) {\
    QJsonValue sub_value;\
    serialize(value.Field, sub_value);\
    js_obj[#Field] = sub_value;}

#define QJSON_SERIALIZER_END(Cls) js_value = js_obj; return js_value;}};\
    template<> QJsonValue& serialize(const Cls& value, QJsonValue& js_value)\
    {\
        return Serializer<Cls>::serialize_(value, js_value);\
    }\
    }}


template <class T>
T& deserialize (T& value, const std::string& str)
{

    return value;
}

template <class T>
const T& serialize (const T& value, std::string& str)
{
    QJsonValue root;
    serialize(value, root);

    QJsonDocument doc(root.toObject());
    str = doc.toJson().toStdString();
    return value;
}

QJSON_SPACE_END
SERIALIZER_SPACE_END

#endif
