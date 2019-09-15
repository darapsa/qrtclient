#ifndef QRTCLIENT_TICKET_HXX
#define QRTCLIENT_TICKET_HXX

#include <QAbstractListModel>

struct rt_ticketlist;

namespace RTClient {

	class Ticket
	{
		public:
			Ticket(QString subject) : m_subject{subject} {}
			QString const& subject() const { return m_subject; }

		private:
			QString m_subject;
	};

	class TicketList : public QAbstractListModel
	{
		Q_OBJECT
		Q_PROPERTY(int rowCount READ rowCount NOTIFY rowCountChanged)

		public:
			enum TicketRoles {
				SubjectRole = Qt::UserRole + 1,
			};

			explicit TicketList(QObject* parent = nullptr)
				: QAbstractListModel{parent} {}
			~TicketList() {}

			int rowCount(QModelIndex const& parent
					= QModelIndex()) const Q_DECL_OVERRIDE;
			QVariant data(const QModelIndex& index
					, int role = Qt::DisplayRole
					) const Q_DECL_OVERRIDE;

		protected:
			QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;

		signals:
			void rowCountChanged();

		private:
			QList<Ticket> tickets;
			void addTicket(Ticket const& ticket);

		private slots:
			void addTickets(struct rt_ticketlist* ticketList);
	};

}

#endif // QRTCLIENT_TICKET_HXX