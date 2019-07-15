#include "db_table.h"

#include <QDebug>
#include <QVBoxLayout>
#include <QSizePolicy>


DBTable::DBTable (QSqlDatabase& db, std::string table, QWidget* parent,
                  Qt::WindowFlags f, std::string sort_by)
                 : QWidget(parent, f)
                 , db(db)
                 , table(table)
                 , sort_by(sort_by)
                 , model(new QSqlQueryModel(this))
                 , view(new QTableView(this)) {
	setLayout(new QVBoxLayout(this));
	view->setModel(model);
	layout()->addWidget(view);
	layout()->setContentsMargins(5, 5, 5, 5);

	model->setQuery(
		QSqlQuery(QString::fromStdString(DBTable::query_string(table, sort_by)), db));

	/* TODO #temp */
	/* if (table != "img") */
	/* 	return; */

	/* { */
	/* 	QDebug deb = qDebug(); */
	/* 	for (int i = 0; i < model->columnCount(); i++) { */
	/* 		deb << model->headerData(i, Qt::Horizontal) << " "; */
	/* 	} */
	/* } */

	/* for (int r = 0; r < model->rowCount(); r++) { */
	/* 	QDebug deb = qDebug(); */
	/* 	for (int c = 0; c < model->columnCount(); c++) { */
	/* 		deb << model->data(model->index(r, c)) << " "; */
	/* 	} */
	/* } */
}

QSqlQueryModel* DBTable::get_model () {
	return model;
}

void DBTable::refresh (const Packet& p) {
	Q_UNUSED(p);
	model->setQuery(model->query());
	model->query().exec();
}

std::string DBTable::query_string(std::string table, std::string sort_by) {
	std::string q_str = "select * from " + table;
	if (!sort_by.empty())
		q_str += " order by " + sort_by + " desc";
	return q_str + ";";
}
