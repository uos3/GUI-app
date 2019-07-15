#include "output_upload.h"

#include "utility.h"


UploaderOutput::UploaderOutput (Uploader& uploader, QObject* parent)
	: Output(parent)
	, uploader(uploader) {}

bool UploaderOutput::do_output (const Buffer& buffer, const Packet& packet) {
	Q_UNUSED(packet);

	QByteArray binary(buffer.get_buf(), buffer.get_len());

	uploader.upload(binary, util::now());

	return true;
}
