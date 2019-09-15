#include <rtclient/client.h>
#include "qrtclient/ticket.hxx"

namespace RTClient {

	int TicketList::rowCount(QModelIndex const& parent) const
	{
		Q_UNUSED(parent)
		return tickets.count();
	}

	QVariant TicketList::data(QModelIndex const& index, int role) const
	{
		auto row = index.row();

		if (row < 0 || row >= tickets.count()) return QVariant();

		auto ticket = tickets[row];
		switch (role) {
			case SubjectRole:
				return ticket.subject();
			default:
				return QVariant();
		}
	}

	QHash<int, QByteArray> TicketList::roleNames() const
	{
		return QHash<int, QByteArray>{
			{SubjectRole, "subject"}
		};
	}

	void TicketList::addTicket(Ticket const& ticket)
	{
		beginInsertRows(QModelIndex(), rowCount(), rowCount());
		tickets << ticket;
		endInsertRows();
		emit rowCountChanged();
	}

	void TicketList::addTickets(rt_ticketlist* ticketList)
	{
		for (unsigned int i = 0; i < ticketList->length; i++)
			addTicket(Ticket{ticketList->tickets[i]});
		rtclient_ticket_freelist(ticketList);
	}

}