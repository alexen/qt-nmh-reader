#include <iostream>

#include <gtest/gtest.h>

#include <QTemporaryFile>
#include <QByteArray>

#include <nmh/io.h>


using alexen::nmh::io::readMessage;
using alexen::nmh::io::writeMessage;

namespace {
namespace testenv {


const QString sourceText = R"txt(Lorem ipsum dolor sit amet,
consectetur adipisicing elit,
sed do eiusmod tempor incididunt
ut labore et dolore magna aliqua.
)txt";

const QByteArray nmhMessage = QByteArray::fromHex(
     "7d0000004c6f72656d20697073756d20646f6c6f722073697420616d6574"
     "2c0a636f6e7365637465747572206164697069736963696e6720656c6974"
     "2c0a73656420646f20656975736d6f642074656d706f7220696e63696469"
     "64756e740a7574206c61626f726520657420646f6c6f7265206d61676e61"
     "20616c697175612e0a"
     );


namespace tools {


void saveRawData( QTemporaryFile& file, const QByteArray& data )
{
     file.open();
     file.write( data );
     file.close();
}


} // namespace tools
} // namespace testenv
} // namespace {anonymous}


TEST( NmhIoTest, WriteMessageTest )
{

     QTemporaryFile tmpFile;
     tmpFile.open();
     ASSERT_TRUE( writeMessage( testenv::sourceText.toLocal8Bit(), tmpFile ) );
     tmpFile.close();
     tmpFile.open();
     ASSERT_EQ( tmpFile.readAll(), testenv::nmhMessage );
}
TEST( NmhIoTest, ReadMessageTest )
{
     QTemporaryFile tmpFile;
     testenv::tools::saveRawData( tmpFile, testenv::nmhMessage );

     tmpFile.open();
     QByteArray content;
     ASSERT_TRUE( readMessage( tmpFile, content ) );
     ASSERT_EQ( content, testenv::sourceText );
}
TEST( NmhIoTest, WriteThenReadMessageTest )
{
     QTemporaryFile tmpFile;
     tmpFile.open();
     ASSERT_TRUE( writeMessage( testenv::sourceText.toLocal8Bit(), tmpFile ) );
     tmpFile.close();
     tmpFile.open();
     QByteArray content;
     ASSERT_TRUE( readMessage( tmpFile, content ) );
     ASSERT_EQ( content, testenv::sourceText );
}
