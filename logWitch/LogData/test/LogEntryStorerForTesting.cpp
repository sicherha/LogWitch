/*
 * LogEntryStorerForTesting.cpp
 *
 *  Created on: 12 Mar 2016
 *      Author: sven
 */

#include <LogData/test/LogEntryStorerForTesting.h>

#include <QCoreApplication>
#include <QTimer>

#include "LogData/LogEntryParser.h"

LogEntryStorerForTesting::LogEntryStorerForTesting(std::unique_ptr<LogEntryParser> parser)
: m_parser(std::move(parser))
{
  auto* parserQO = dynamic_cast<QObject*>(m_parser.get());

  QObject::connect(parserQO, SIGNAL(newEntry(TconstSharedNewLogEntryMessage)), this, SLOT(onNewEntry(TconstSharedNewLogEntryMessage)));
  QObject::connect(parserQO, SIGNAL(signalError(QString)), this, SLOT(onSignalError(QString)));
  QObject::connect(parserQO, SIGNAL(finished()), this, SLOT(onFinished()));
}

LogEntryStorerForTesting::~LogEntryStorerForTesting() = default;

void LogEntryStorerForTesting::start()
{
  int argc =0;
  char * argv[] = {nullptr};
  QCoreApplication app(argc, argv);
  m_app = &app;

  // Ensure we will not test forever in error cases
  QTimer::singleShot(20000, &app, &QCoreApplication::quit);
  QTimer::singleShot(0, this, &LogEntryStorerForTesting::runParser);
  app.exec();

  m_app = nullptr;
}

void LogEntryStorerForTesting::runParser()
{
  if (!m_parser->initParser())
    m_app->quit();

  m_parser->startEmiting();
}

void LogEntryStorerForTesting::onNewEntry( TconstSharedNewLogEntryMessage msg )
{
  m_entryMessages.push_back(msg);
  m_entries.insert( m_entries.end(), msg->entries.begin(), msg->entries.end());
}

void LogEntryStorerForTesting::onSignalError( QString error )
{
  m_errors.push_back( error );
}

void LogEntryStorerForTesting::onFinished()
{
  m_finished = true;
  if (m_app)
    m_app->quit();
}
