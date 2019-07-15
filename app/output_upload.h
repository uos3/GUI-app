#pragma once

#include "output.h"
#include "uploader.h"


// for uploading new packets to the remote database.
class UploaderOutput : public Output
{
	Q_OBJECT

public:
	UploaderOutput (Uploader& uploader, QObject* parent=nullptr);

protected:
	bool do_output (const Buffer& buffer, const Packet& packet) override;

private:
	Uploader& uploader;
};
