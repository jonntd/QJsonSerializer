#ifndef QJSONSERIALIZER_H
#define QJSONSERIALIZER_H

#include <QByteArray>
#include <QIODevice>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMetaObject>
#include <QMetaProperty>
#include <QDebug>
#include <QJsonArray>

#include "Array.h"
#include "IDeserializer.h"
#include "IObjectFactory.h"
#include "ISerializer.h"

class Q_DECL_EXPORT QJsonSerializer
{
	public:
		QJsonSerializer();

		void setObjectFactory(IObjectFactory *factory);

		template<class TReturn>
		TReturn deserialize(const QByteArray &data)
		{
			Deserializer<TReturn> subject(*m_factory);

			return subject.deserialize(data);
		}

		template<class TReturn>
		void deserialize(const QByteArray &data, TReturn target)
		{
			Deserializer<TReturn> subject(*m_factory);

			subject.deserialize(data, target);
		}

		template<class TReturn>
		TReturn deserialize(QIODevice *device)
		{
			const QByteArray &data = device->readAll();

			return deserialize<TReturn>(data);
		}

		template<class TReturn>
		void deserialize(QIODevice *device, TReturn target)
		{
			const QByteArray &data = device->readAll();

			deserialize(data, target);
		}

		template<class TSource>
		QByteArray serialize(const TSource &source)
		{
			Serializer<TSource> subject;

			return subject.serialize(source);
		}

	private:
		DefaultObjectFactory m_defaultFactory;
		IObjectFactory *m_factory;
};

#endif // QJSONSERIALIZER_H
