#include "packet.h"
#include "utility.h"

#include <ctime>

/* Overloaded from_buffer functions that extract data from the buffer into the
corresponding structs */

void from_buffer (GPS& g, Buffer& b) {
	b.set_pos(248);
	uint16_t seq_id = static_cast<uint16_t>(b.get(16));
/* TODO #temp: '\0's on these */
	char sequence_id[3] = { static_cast<char>((seq_id >> 8)),
							static_cast<char>((seq_id & 0xFF)), '\0' };
/* TODO #temp: 3 (was 2) & elsewhere */
	std::copy(sequence_id, sequence_id+3, g.sequence_id);
	g.timestamp = b.get(32);
/* TODO #temp: clamping these values -- hopefully shouldn't need to for real
 *             data (should have been dealt with earlier in the pipeline) */
	g.lat = qMax( -90.f, qMin(static_cast<float>(b.get(32)),  90.f));
	g.lon = qMax(-180.f, qMin(static_cast<float>(b.get(32)), 180.f));
	g.alt = static_cast<float>(b.get(32));
	g.hdop = static_cast<uint8_t>(b.get(8));
	g.vdop = static_cast<uint8_t>(b.get(8));
	g.pdop = static_cast<uint8_t>(b.get(8));
	g.tdop = static_cast<uint8_t>(b.get(8));
}

void from_buffer (IMU& i, Buffer& b) {
	b.set_pos(248);
	uint16_t seq_id = static_cast<uint16_t>(b.get(16));
	char sequence_id[3] = { static_cast<char>((seq_id >> 8)),
							static_cast<char>((seq_id & 0xFF)), '\0' };
	std::copy(sequence_id, sequence_id+3, i.sequence_id);
	i.timestamp = b.get(32);
	uint16_t mag_x[5];
	for (int i=0; i<5; i++) { mag_x[i] = static_cast<uint16_t>(b.get(16)); }
	std::copy(mag_x, mag_x+5, i.mag_x);
	uint16_t mag_y[5];
	for (int i=0; i<5; i++) { mag_y[i] = static_cast<uint16_t>(b.get(16)); }
	std::copy(mag_y, mag_y+5, i.mag_y);
	uint16_t mag_z[5];
	for (int i=0; i<5; i++) { mag_z[i] = static_cast<uint16_t>(b.get(16)); }
	std::copy(mag_z, mag_z+5, i.mag_z);
	uint16_t gyro_x[5];
	for (int i=0; i<5; i++) { gyro_x[i] = static_cast<uint16_t>(b.get(16)); }
	std::copy(gyro_x, gyro_x+5, i.gyro_x);
	uint16_t gyro_y[5];
	for (int i=0; i<5; i++) { gyro_y[i] = static_cast<uint16_t>(b.get(16)); }
	std::copy(gyro_y, gyro_y+5, i.gyro_y);
	uint16_t gyro_z[5];
	for (int i=0; i<5; i++) { gyro_z[i] = static_cast<uint16_t>(b.get(16)); }
	std::copy(gyro_z, gyro_z+5, i.gyro_z);
	uint16_t accel_x[5];
	for (int i=0; i<5; i++) { accel_x[i] = static_cast<uint16_t>(b.get(16)); }
	std::copy(accel_x, accel_x+5, i.accel_x);
	uint16_t accel_y[5];
	for (int i=0; i<5; i++) { accel_y[i] = static_cast<uint16_t>(b.get(16)); }
	std::copy(accel_y, accel_y+5, i.accel_y);
	uint16_t accel_z[5];
	for (int i=0; i<5; i++) { accel_z[i] = static_cast<uint16_t>(b.get(16)); }
	std::copy(accel_z, accel_z+5, i.accel_z);
}

void from_buffer (Img& i, Buffer& b) {
	b.set_pos(248);
	uint16_t seq_id = static_cast<uint16_t>(b.get(16));
	char sequence_id[3] = { static_cast<char>((seq_id >> 8)),
							static_cast<char>((seq_id & 0xFF)), '\0' };
	std::copy(sequence_id, sequence_id+3, i.sequence_id);
	i.timestamp = b.get(32);
	i.image_id = static_cast<uint8_t>(b.get(8));
	i.fragment_id = static_cast<uint16_t>(b.get(16));
	i.num_fragments = static_cast<uint16_t>(b.get(16));
	char image_data[76];
	uint64_t fragment_len = b.len()-(b.pos()+144);
	uint32_t num_bytes = fragment_len/8;
	uint8_t num_bits = fragment_len%8;
	for(int i=0; i<num_bytes; i++) { image_data[i] = static_cast<char>b.get(8); }
    	image_data[num_bytes] = static_cast<char>b.get(num_bits);
	std::copy(image_data, image_data+num_bytes, i.image_data);
}

void from_buffer (Health& h, Buffer& b) {
	b.set_pos(248);
	uint16_t seq_id = static_cast<uint16_t>(b.get(16));
	char sequence_id[3] = { static_cast<char>((seq_id >> 8)),
							static_cast<char>((seq_id & 0xFF)), '\0' };
	std::copy(sequence_id, sequence_id+3, h.sequence_id);
	h.timestamp = b.get(32);
	h.obc_temperature = static_cast<uint8_t>(b.get(8));
	h.rx_temperature = static_cast<uint8_t>(b.get(8));
	h.tx_temperature = static_cast<uint8_t>(b.get(8));
	h.pa_temperature = static_cast<uint8_t>(b.get(8));
	h.reboot_count = static_cast<uint8_t>(b.get(8));
	h.data_packets_pending = static_cast<uint16_t>(b.get(16));
	h.antenna_switch = static_cast<bool>(b.get(1));
	h.rx_noisefloor = static_cast<uint8_t>(b.get(8));
	h.detected_flash_errors = static_cast<uint8_t>(b.get(4));
	h.detected_ram_errors = static_cast<uint8_t>(b.get(4));
	h.battery_voltage = static_cast<uint16_t>(b.get(10));
	h.battery_current = static_cast<uint16_t>(b.get(10));
	h.battery_temperature = static_cast<uint16_t>(b.get(10));
	h.charge_current = static_cast<uint16_t>(b.get(10));
	h.mppt_voltage = static_cast<uint16_t>(b.get(10));
	h.solar_n1_current = static_cast<uint16_t>(b.get(10));
	h.solar_n2_current = static_cast<uint16_t>(b.get(10));
	h.solar_e1_current = static_cast<uint16_t>(b.get(10));
	h.solar_e2_current = static_cast<uint16_t>(b.get(10));
	h.solar_s1_current = static_cast<uint16_t>(b.get(10));
	h.solar_s2_current = static_cast<uint16_t>(b.get(10));
	h.solar_w1_current = static_cast<uint16_t>(b.get(10));
	h.solar_w2_current = static_cast<uint16_t>(b.get(10));
	h.solar_t1_current = static_cast<uint16_t>(b.get(10));
	h.solar_t2_current = static_cast<uint16_t>(b.get(10));
	bool rails_switch_status[6] = {
		static_cast<bool>(b.get(1)), static_cast<bool>(b.get(1)),
		static_cast<bool>(b.get(1)), static_cast<bool>(b.get(1)),
		static_cast<bool>(b.get(1)), static_cast<bool>(b.get(1))
	};
	std::copy(rails_switch_status, rails_switch_status+6, h.rails_switch_status);
	bool rails_overcurrent_status[6] = {
		static_cast<bool>(b.get(1)), static_cast<bool>(b.get(1)),
		static_cast<bool>(b.get(1)), static_cast<bool>(b.get(1)),
		static_cast<bool>(b.get(1)), static_cast<bool>(b.get(1))
	};
	std::copy(rails_overcurrent_status, rails_overcurrent_status+6, h.rails_overcurrent_status);
	h.rail_1_boot_count = static_cast<uint16_t>(b.get(16));
	h.rail_1_overcurrent_count = static_cast<uint16_t>(b.get(16));
	h.rail_1_voltage = static_cast<uint16_t>(b.get(10));
	h.rail_1_current = static_cast<uint16_t>(b.get(10));
	h.rail_2_boot_count = static_cast<uint16_t>(b.get(16));
	h.rail_2_overcurrent_count = static_cast<uint16_t>(b.get(16));
	h.rail_2_voltage = static_cast<uint16_t>(b.get(10));
	h.rail_2_current = static_cast<uint16_t>(b.get(10));
	h.rail_3_boot_count = static_cast<uint16_t>(b.get(16));
	h.rail_3_overcurrent_count = static_cast<uint16_t>(b.get(16));
	h.rail_3_voltage = static_cast<uint16_t>(b.get(10));
	h.rail_3_current = static_cast<uint16_t>(b.get(10));
	h.rail_4_boot_count = static_cast<uint16_t>(b.get(16));
	h.rail_4_overcurrent_count = static_cast<uint16_t>(b.get(16));
	h.rail_4_voltage = static_cast<uint16_t>(b.get(10));
	h.rail_4_current = static_cast<uint16_t>(b.get(10));
	h.rail_5_boot_count = static_cast<uint16_t>(b.get(16));
	h.rail_5_overcurrent_count = static_cast<uint16_t>(b.get(16));
	h.rail_5_voltage = static_cast<uint16_t>(b.get(10));
	h.rail_5_current = static_cast<uint16_t>(b.get(10));
	h.rail_6_boot_count = static_cast<uint16_t>(b.get(16));
	h.rail_6_overcurrent_count = static_cast<uint16_t>(b.get(16));
	h.rail_6_voltage = static_cast<uint16_t>(b.get(10));
	h.rail_6_current = static_cast<uint16_t>(b.get(10));
	h._3v3_voltage = static_cast<uint16_t>(b.get(10));
	h._3v3_current = static_cast<uint16_t>(b.get(10));
	h._5v_voltage = static_cast<uint16_t>(b.get(10));
	h._5v_current = static_cast<uint16_t>(b.get(10));
}

void from_buffer (Status& s, Buffer& b) {
	b.set_pos(80);
	uint16_t spc_id = static_cast<uint16_t>(b.get(16));
	char spacecraft_id[3] = { static_cast<char>((spc_id >> 8)),
							static_cast<char>((spc_id & 0xFF)), '\0' };
	std::copy(spacecraft_id, spacecraft_id+3, s.spacecraft_id);
	s.time = b.get(32);
	s.time_source = static_cast<bool>(b.get(1));
	uint16_t seq_id = static_cast<uint16_t>(b.get(16));
/* TODO #temp */
	qDebug () << (seq_id >> 8) << " & " << (seq_id & 0xFF);
	char sequence_id[3] = { static_cast<char>((seq_id >> 8)),
							static_cast<char>((seq_id & 0xFF)), '\0' };
	std::copy(sequence_id, sequence_id+3, s.sequence_id);
	s.obc_temperature = static_cast<uint8_t>(b.get(8));
	s.battery_temperature = static_cast<uint8_t>(b.get(8));
	s.battery_voltage = static_cast<uint8_t>(b.get(8));
	s.battery_current = static_cast<uint8_t>(b.get(8));
	s.charge_current = static_cast<uint8_t>(b.get(8));
	s.antenna_deployment = static_cast<bool>(b.get(1));
	s.data_pending = static_cast<uint16_t>(b.get(16));
	s.reboot_count = static_cast<uint8_t>(b.get(8));
	bool rails_status[6] = {
		static_cast<bool>(b.get(1)), static_cast<bool>(b.get(1)),
		static_cast<bool>(b.get(1)), static_cast<bool>(b.get(1)),
		static_cast<bool>(b.get(1)), static_cast<bool>(b.get(1))
	};
	std::copy(rails_status, rails_status+6, s.rails_status);
	s.rx_temperature = static_cast<uint8_t>(b.get(8));
	s.tx_temperature = static_cast<uint8_t>(b.get(8));
	s.pa_temperature = static_cast<uint8_t>(b.get(8));
	s.rx_noisefloor = static_cast<uint8_t>(b.get(8));
}

void from_buffer (Packet& p, Buffer& b) {
	from_buffer(p, b, util::now());
}

void from_buffer (Packet& p, Buffer& b, uint32_t downlink_time) {
	b.set_pos(64);
	p.type = static_cast<PayloadType>(b.get(16));
	from_buffer(p.status, b);
	switch (p.type) {
		case PayloadType::GPS:
			from_buffer(p.payload.gps, b);
			break;
		case PayloadType::IMU:
			from_buffer(p.payload.imu, b);
			break;
		case PayloadType::Health:
			from_buffer(p.payload.health, b);
			break;
		case PayloadType::Img:
			from_buffer(p.payload.img, b);
			break;
		case PayloadType::Config:
			// TODO #bug: Needs finishing
			break;
		default:
			std::string msg = "invalid payload type \"";
			msg += std::to_string(static_cast<int>(p.type));
			msg += "\" while parsing packet.";
			throw std::runtime_error(msg);
			break;
	}
	// current UTC time as a unix timestamp.
	p.downlink_time = downlink_time;
	// TODO #verify: assumes crc & hash occupy last 144 bits of packet (as
	//			   opposed to the 144 bits that come after the payload).
	strncpy(p.hash, b.get_buf()+b.get_len()-18*8, 16);
	strncpy(p.crc, b.get_buf()+b.get_len()-2*8, 2);
/* TODO #temp */
	p.crc[2] = '\0';
	p.hash[16] = '\0';
}
