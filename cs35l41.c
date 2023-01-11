#include "cs35l41.h"
#include "registers.h"
#include "cs35l41_fw.h"

#define bool int

static ULONG Cs35l41DebugLevel = 100;
static ULONG Cs35l41DebugCatagories = DBG_INIT || DBG_PNP || DBG_IOCTL;

static const struct cs35l41_otp_packed_element_t otp_map_1[] = {
	/* addr         shift   size */
	{ 0x00002030,	0,	4 }, /*TRIM_OSC_FREQ_TRIM*/
	{ 0x00002030,	7,	1 }, /*TRIM_OSC_TRIM_DONE*/
	{ 0x0000208c,	24,	6 }, /*TST_DIGREG_VREF_TRIM*/
	{ 0x00002090,	14,	4 }, /*TST_REF_TRIM*/
	{ 0x00002090,	10,	4 }, /*TST_REF_TEMPCO_TRIM*/
	{ 0x0000300C,	11,	4 }, /*PLL_LDOA_TST_VREF_TRIM*/
	{ 0x0000394C,	23,	2 }, /*BST_ATEST_CM_VOFF*/
	{ 0x00003950,	0,	7 }, /*BST_ATRIM_IADC_OFFSET*/
	{ 0x00003950,	8,	7 }, /*BST_ATRIM_IADC_GAIN1*/
	{ 0x00003950,	16,	8 }, /*BST_ATRIM_IPKCOMP_OFFSET1*/
	{ 0x00003950,	24,	8 }, /*BST_ATRIM_IPKCOMP_GAIN1*/
	{ 0x00003954,	0,	7 }, /*BST_ATRIM_IADC_OFFSET2*/
	{ 0x00003954,	8,	7 }, /*BST_ATRIM_IADC_GAIN2*/
	{ 0x00003954,	16,	8 }, /*BST_ATRIM_IPKCOMP_OFFSET2*/
	{ 0x00003954,	24,	8 }, /*BST_ATRIM_IPKCOMP_GAIN2*/
	{ 0x00003958,	0,	7 }, /*BST_ATRIM_IADC_OFFSET3*/
	{ 0x00003958,	8,	7 }, /*BST_ATRIM_IADC_GAIN3*/
	{ 0x00003958,	16,	8 }, /*BST_ATRIM_IPKCOMP_OFFSET3*/
	{ 0x00003958,	24,	8 }, /*BST_ATRIM_IPKCOMP_GAIN3*/
	{ 0x0000395C,	0,	7 }, /*BST_ATRIM_IADC_OFFSET4*/
	{ 0x0000395C,	8,	7 }, /*BST_ATRIM_IADC_GAIN4*/
	{ 0x0000395C,	16,	8 }, /*BST_ATRIM_IPKCOMP_OFFSET4*/
	{ 0x0000395C,	24,	8 }, /*BST_ATRIM_IPKCOMP_GAIN4*/
	{ 0x0000416C,	0,	8 }, /*VMON_GAIN_OTP_VAL*/
	{ 0x00004160,	0,	7 }, /*VMON_OFFSET_OTP_VAL*/
	{ 0x0000416C,	8,	8 }, /*IMON_GAIN_OTP_VAL*/
	{ 0x00004160,	16,	10 }, /*IMON_OFFSET_OTP_VAL*/
	{ 0x0000416C,	16,	12 }, /*VMON_CM_GAIN_OTP_VAL*/
	{ 0x0000416C,	28,	1 }, /*VMON_CM_GAIN_SIGN_OTP_VAL*/
	{ 0x00004170,	0,	6 }, /*IMON_CAL_TEMPCO_OTP_VAL*/
	{ 0x00004170,	6,	1 }, /*IMON_CAL_TEMPCO_SIGN_OTP*/
	{ 0x00004170,	8,	6 }, /*IMON_CAL_TEMPCO2_OTP_VAL*/
	{ 0x00004170,	14,	1 }, /*IMON_CAL_TEMPCO2_DN_UPB_OTP_VAL*/
	{ 0x00004170,	16,	9 }, /*IMON_CAL_TEMPCO_TBASE_OTP_VAL*/
	{ 0x00004360,	0,	5 }, /*TEMP_GAIN_OTP_VAL*/
	{ 0x00004360,	6,	9 }, /*TEMP_OFFSET_OTP_VAL*/
	{ 0x00004448,	0,	8 }, /*VP_SARADC_OFFSET*/
	{ 0x00004448,	8,	8 }, /*VP_GAIN_INDEX*/
	{ 0x00004448,	16,	8 }, /*VBST_SARADC_OFFSET*/
	{ 0x00004448,	24,	8 }, /*VBST_GAIN_INDEX*/
	{ 0x0000444C,	0,	3 }, /*ANA_SELINVREF*/
	{ 0x00006E30,	0,	5 }, /*GAIN_ERR_COEFF_0*/
	{ 0x00006E30,	8,	5 }, /*GAIN_ERR_COEFF_1*/
	{ 0x00006E30,	16,	5 }, /*GAIN_ERR_COEFF_2*/
	{ 0x00006E30,	24,	5 }, /*GAIN_ERR_COEFF_3*/
	{ 0x00006E34,	0,	5 }, /*GAIN_ERR_COEFF_4*/
	{ 0x00006E34,	8,	5 }, /*GAIN_ERR_COEFF_5*/
	{ 0x00006E34,	16,	5 }, /*GAIN_ERR_COEFF_6*/
	{ 0x00006E34,	24,	5 }, /*GAIN_ERR_COEFF_7*/
	{ 0x00006E38,	0,	5 }, /*GAIN_ERR_COEFF_8*/
	{ 0x00006E38,	8,	5 }, /*GAIN_ERR_COEFF_9*/
	{ 0x00006E38,	16,	5 }, /*GAIN_ERR_COEFF_10*/
	{ 0x00006E38,	24,	5 }, /*GAIN_ERR_COEFF_11*/
	{ 0x00006E3C,	0,	5 }, /*GAIN_ERR_COEFF_12*/
	{ 0x00006E3C,	8,	5 }, /*GAIN_ERR_COEFF_13*/
	{ 0x00006E3C,	16,	5 }, /*GAIN_ERR_COEFF_14*/
	{ 0x00006E3C,	24,	5 }, /*GAIN_ERR_COEFF_15*/
	{ 0x00006E40,	0,	5 }, /*GAIN_ERR_COEFF_16*/
	{ 0x00006E40,	8,	5 }, /*GAIN_ERR_COEFF_17*/
	{ 0x00006E40,	16,	5 }, /*GAIN_ERR_COEFF_18*/
	{ 0x00006E40,	24,	5 }, /*GAIN_ERR_COEFF_19*/
	{ 0x00006E44,	0,	5 }, /*GAIN_ERR_COEFF_20*/
	{ 0x00006E48,	0,	10 }, /*VOFF_GAIN_0*/
	{ 0x00006E48,	10,	10 }, /*VOFF_GAIN_1*/
	{ 0x00006E48,	20,	10 }, /*VOFF_GAIN_2*/
	{ 0x00006E4C,	0,	10 }, /*VOFF_GAIN_3*/
	{ 0x00006E4C,	10,	10 }, /*VOFF_GAIN_4*/
	{ 0x00006E4C,	20,	10 }, /*VOFF_GAIN_5*/
	{ 0x00006E50,	0,	10 }, /*VOFF_GAIN_6*/
	{ 0x00006E50,	10,	10 }, /*VOFF_GAIN_7*/
	{ 0x00006E50,	20,	10 }, /*VOFF_GAIN_8*/
	{ 0x00006E54,	0,	10 }, /*VOFF_GAIN_9*/
	{ 0x00006E54,	10,	10 }, /*VOFF_GAIN_10*/
	{ 0x00006E54,	20,	10 }, /*VOFF_GAIN_11*/
	{ 0x00006E58,	0,	10 }, /*VOFF_GAIN_12*/
	{ 0x00006E58,	10,	10 }, /*VOFF_GAIN_13*/
	{ 0x00006E58,	20,	10 }, /*VOFF_GAIN_14*/
	{ 0x00006E5C,	0,	10 }, /*VOFF_GAIN_15*/
	{ 0x00006E5C,	10,	10 }, /*VOFF_GAIN_16*/
	{ 0x00006E5C,	20,	10 }, /*VOFF_GAIN_17*/
	{ 0x00006E60,	0,	10 }, /*VOFF_GAIN_18*/
	{ 0x00006E60,	10,	10 }, /*VOFF_GAIN_19*/
	{ 0x00006E60,	20,	10 }, /*VOFF_GAIN_20*/
	{ 0x00006E64,	0,	10 }, /*VOFF_INT1*/
	{ 0x00007418,	7,	5 }, /*DS_SPK_INT1_CAP_TRIM*/
	{ 0x0000741C,	0,	5 }, /*DS_SPK_INT2_CAP_TRIM*/
	{ 0x0000741C,	11,	4 }, /*DS_SPK_LPF_CAP_TRIM*/
	{ 0x0000741C,	19,	4 }, /*DS_SPK_QUAN_CAP_TRIM*/
	{ 0x00007434,	17,	1 }, /*FORCE_CAL*/
	{ 0x00007434,	18,	7 }, /*CAL_OVERRIDE*/
	{ 0x00007068,	0,	9 }, /*MODIX*/
	{ 0x0000410C,	7,	1 }, /*VIMON_DLY_NOT_COMB*/
	{ 0x0000400C,	0,	7 }, /*VIMON_DLY*/
	{ 0x00000000,	0,	1 }, /*extra bit*/
	{ 0x00017040,	0,	8 }, /*X_COORDINATE*/
	{ 0x00017040,	8,	8 }, /*Y_COORDINATE*/
	{ 0x00017040,	16,	8 }, /*WAFER_ID*/
	{ 0x00017040,	24,	8 }, /*DVS*/
	{ 0x00017044,	0,	24 }, /*LOT_NUMBER*/
};

static const struct cs35l41_otp_packed_element_t otp_map_2[] = {
	/* addr         shift   size */
	{ 0x00002030,	0,	4 }, /*TRIM_OSC_FREQ_TRIM*/
	{ 0x00002030,	7,	1 }, /*TRIM_OSC_TRIM_DONE*/
	{ 0x0000208c,	24,	6 }, /*TST_DIGREG_VREF_TRIM*/
	{ 0x00002090,	14,	4 }, /*TST_REF_TRIM*/
	{ 0x00002090,	10,	4 }, /*TST_REF_TEMPCO_TRIM*/
	{ 0x0000300C,	11,	4 }, /*PLL_LDOA_TST_VREF_TRIM*/
	{ 0x0000394C,	23,	2 }, /*BST_ATEST_CM_VOFF*/
	{ 0x00003950,	0,	7 }, /*BST_ATRIM_IADC_OFFSET*/
	{ 0x00003950,	8,	7 }, /*BST_ATRIM_IADC_GAIN1*/
	{ 0x00003950,	16,	8 }, /*BST_ATRIM_IPKCOMP_OFFSET1*/
	{ 0x00003950,	24,	8 }, /*BST_ATRIM_IPKCOMP_GAIN1*/
	{ 0x00003954,	0,	7 }, /*BST_ATRIM_IADC_OFFSET2*/
	{ 0x00003954,	8,	7 }, /*BST_ATRIM_IADC_GAIN2*/
	{ 0x00003954,	16,	8 }, /*BST_ATRIM_IPKCOMP_OFFSET2*/
	{ 0x00003954,	24,	8 }, /*BST_ATRIM_IPKCOMP_GAIN2*/
	{ 0x00003958,	0,	7 }, /*BST_ATRIM_IADC_OFFSET3*/
	{ 0x00003958,	8,	7 }, /*BST_ATRIM_IADC_GAIN3*/
	{ 0x00003958,	16,	8 }, /*BST_ATRIM_IPKCOMP_OFFSET3*/
	{ 0x00003958,	24,	8 }, /*BST_ATRIM_IPKCOMP_GAIN3*/
	{ 0x0000395C,	0,	7 }, /*BST_ATRIM_IADC_OFFSET4*/
	{ 0x0000395C,	8,	7 }, /*BST_ATRIM_IADC_GAIN4*/
	{ 0x0000395C,	16,	8 }, /*BST_ATRIM_IPKCOMP_OFFSET4*/
	{ 0x0000395C,	24,	8 }, /*BST_ATRIM_IPKCOMP_GAIN4*/
	{ 0x0000416C,	0,	8 }, /*VMON_GAIN_OTP_VAL*/
	{ 0x00004160,	0,	7 }, /*VMON_OFFSET_OTP_VAL*/
	{ 0x0000416C,	8,	8 }, /*IMON_GAIN_OTP_VAL*/
	{ 0x00004160,	16,	10 }, /*IMON_OFFSET_OTP_VAL*/
	{ 0x0000416C,	16,	12 }, /*VMON_CM_GAIN_OTP_VAL*/
	{ 0x0000416C,	28,	1 }, /*VMON_CM_GAIN_SIGN_OTP_VAL*/
	{ 0x00004170,	0,	6 }, /*IMON_CAL_TEMPCO_OTP_VAL*/
	{ 0x00004170,	6,	1 }, /*IMON_CAL_TEMPCO_SIGN_OTP*/
	{ 0x00004170,	8,	6 }, /*IMON_CAL_TEMPCO2_OTP_VAL*/
	{ 0x00004170,	14,	1 }, /*IMON_CAL_TEMPCO2_DN_UPB_OTP_VAL*/
	{ 0x00004170,	16,	9 }, /*IMON_CAL_TEMPCO_TBASE_OTP_VAL*/
	{ 0x00004360,	0,	5 }, /*TEMP_GAIN_OTP_VAL*/
	{ 0x00004360,	6,	9 }, /*TEMP_OFFSET_OTP_VAL*/
	{ 0x00004448,	0,	8 }, /*VP_SARADC_OFFSET*/
	{ 0x00004448,	8,	8 }, /*VP_GAIN_INDEX*/
	{ 0x00004448,	16,	8 }, /*VBST_SARADC_OFFSET*/
	{ 0x00004448,	24,	8 }, /*VBST_GAIN_INDEX*/
	{ 0x0000444C,	0,	3 }, /*ANA_SELINVREF*/
	{ 0x00006E30,	0,	5 }, /*GAIN_ERR_COEFF_0*/
	{ 0x00006E30,	8,	5 }, /*GAIN_ERR_COEFF_1*/
	{ 0x00006E30,	16,	5 }, /*GAIN_ERR_COEFF_2*/
	{ 0x00006E30,	24,	5 }, /*GAIN_ERR_COEFF_3*/
	{ 0x00006E34,	0,	5 }, /*GAIN_ERR_COEFF_4*/
	{ 0x00006E34,	8,	5 }, /*GAIN_ERR_COEFF_5*/
	{ 0x00006E34,	16,	5 }, /*GAIN_ERR_COEFF_6*/
	{ 0x00006E34,	24,	5 }, /*GAIN_ERR_COEFF_7*/
	{ 0x00006E38,	0,	5 }, /*GAIN_ERR_COEFF_8*/
	{ 0x00006E38,	8,	5 }, /*GAIN_ERR_COEFF_9*/
	{ 0x00006E38,	16,	5 }, /*GAIN_ERR_COEFF_10*/
	{ 0x00006E38,	24,	5 }, /*GAIN_ERR_COEFF_11*/
	{ 0x00006E3C,	0,	5 }, /*GAIN_ERR_COEFF_12*/
	{ 0x00006E3C,	8,	5 }, /*GAIN_ERR_COEFF_13*/
	{ 0x00006E3C,	16,	5 }, /*GAIN_ERR_COEFF_14*/
	{ 0x00006E3C,	24,	5 }, /*GAIN_ERR_COEFF_15*/
	{ 0x00006E40,	0,	5 }, /*GAIN_ERR_COEFF_16*/
	{ 0x00006E40,	8,	5 }, /*GAIN_ERR_COEFF_17*/
	{ 0x00006E40,	16,	5 }, /*GAIN_ERR_COEFF_18*/
	{ 0x00006E40,	24,	5 }, /*GAIN_ERR_COEFF_19*/
	{ 0x00006E44,	0,	5 }, /*GAIN_ERR_COEFF_20*/
	{ 0x00006E48,	0,	10 }, /*VOFF_GAIN_0*/
	{ 0x00006E48,	10,	10 }, /*VOFF_GAIN_1*/
	{ 0x00006E48,	20,	10 }, /*VOFF_GAIN_2*/
	{ 0x00006E4C,	0,	10 }, /*VOFF_GAIN_3*/
	{ 0x00006E4C,	10,	10 }, /*VOFF_GAIN_4*/
	{ 0x00006E4C,	20,	10 }, /*VOFF_GAIN_5*/
	{ 0x00006E50,	0,	10 }, /*VOFF_GAIN_6*/
	{ 0x00006E50,	10,	10 }, /*VOFF_GAIN_7*/
	{ 0x00006E50,	20,	10 }, /*VOFF_GAIN_8*/
	{ 0x00006E54,	0,	10 }, /*VOFF_GAIN_9*/
	{ 0x00006E54,	10,	10 }, /*VOFF_GAIN_10*/
	{ 0x00006E54,	20,	10 }, /*VOFF_GAIN_11*/
	{ 0x00006E58,	0,	10 }, /*VOFF_GAIN_12*/
	{ 0x00006E58,	10,	10 }, /*VOFF_GAIN_13*/
	{ 0x00006E58,	20,	10 }, /*VOFF_GAIN_14*/
	{ 0x00006E5C,	0,	10 }, /*VOFF_GAIN_15*/
	{ 0x00006E5C,	10,	10 }, /*VOFF_GAIN_16*/
	{ 0x00006E5C,	20,	10 }, /*VOFF_GAIN_17*/
	{ 0x00006E60,	0,	10 }, /*VOFF_GAIN_18*/
	{ 0x00006E60,	10,	10 }, /*VOFF_GAIN_19*/
	{ 0x00006E60,	20,	10 }, /*VOFF_GAIN_20*/
	{ 0x00006E64,	0,	10 }, /*VOFF_INT1*/
	{ 0x00007418,	7,	5 }, /*DS_SPK_INT1_CAP_TRIM*/
	{ 0x0000741C,	0,	5 }, /*DS_SPK_INT2_CAP_TRIM*/
	{ 0x0000741C,	11,	4 }, /*DS_SPK_LPF_CAP_TRIM*/
	{ 0x0000741C,	19,	4 }, /*DS_SPK_QUAN_CAP_TRIM*/
	{ 0x00007434,	17,	1 }, /*FORCE_CAL*/
	{ 0x00007434,	18,	7 }, /*CAL_OVERRIDE*/
	{ 0x00007068,	0,	9 }, /*MODIX*/
	{ 0x0000410C,	7,	1 }, /*VIMON_DLY_NOT_COMB*/
	{ 0x0000400C,	0,	7 }, /*VIMON_DLY*/
	{ 0x00004000,	11,	1 }, /*VMON_POL*/
	{ 0x00017040,	0,	8 }, /*X_COORDINATE*/
	{ 0x00017040,	8,	8 }, /*Y_COORDINATE*/
	{ 0x00017040,	16,	8 }, /*WAFER_ID*/
	{ 0x00017040,	24,	8 }, /*DVS*/
	{ 0x00017044,	0,	24 }, /*LOT_NUMBER*/
};

static const struct cs35l41_otp_map_element_t cs35l41_otp_map_map[] = {
	{
		.id = 0x01,
		.map = otp_map_1,
		.num_elements = ARRAYSIZE(otp_map_1),
		.bit_offset = 16,
		.word_offset = 2,
	},
	{
		.id = 0x02,
		.map = otp_map_2,
		.num_elements = ARRAYSIZE(otp_map_2),
		.bit_offset = 16,
		.word_offset = 2,
	},
	{
		.id = 0x03,
		.map = otp_map_2,
		.num_elements = ARRAYSIZE(otp_map_2),
		.bit_offset = 16,
		.word_offset = 2,
	},
	{
		.id = 0x06,
		.map = otp_map_2,
		.num_elements = ARRAYSIZE(otp_map_2),
		.bit_offset = 16,
		.word_offset = 2,
	},
	{
		.id = 0x08,
		.map = otp_map_1,
		.num_elements = ARRAYSIZE(otp_map_1),
		.bit_offset = 16,
		.word_offset = 2,
	},
};

NTSTATUS
DriverEntry(
	__in PDRIVER_OBJECT  DriverObject,
	__in PUNICODE_STRING RegistryPath
)
{
	NTSTATUS               status = STATUS_SUCCESS;
	WDF_DRIVER_CONFIG      config;
	WDF_OBJECT_ATTRIBUTES  attributes;

	Cs35l41Print(DEBUG_LEVEL_INFO, DBG_INIT,
		"Driver Entry\n");

	WDF_DRIVER_CONFIG_INIT(&config, Cs35l41EvtDeviceAdd);

	WDF_OBJECT_ATTRIBUTES_INIT(&attributes);

	//
	// Create a framework driver object to represent our driver.
	//

	status = WdfDriverCreate(DriverObject,
		RegistryPath,
		&attributes,
		&config,
		WDF_NO_HANDLE
	);

	if (!NT_SUCCESS(status))
	{
		Cs35l41Print(DEBUG_LEVEL_ERROR, DBG_INIT,
			"WdfDriverCreate failed with status 0x%x\n", status);
	}

	return status;
}

NTSTATUS cs35l41_reg_write(PCS35L41_CONTEXT pDevice, uint32_t reg, uint32_t data)
{
	uint8_t buf[8];

	buf[0] = (reg >> 24) & 0xFF;
	buf[1] = (reg >> 16) & 0xFF;
	buf[2] = (reg >> 8) & 0xFF;
	buf[3] = reg & 0xFF;
	buf[4] = (data >> 24) & 0xFF;
	buf[5] = (data >> 16) & 0xFF;
	buf[6] = (data >> 8) & 0xFF;
	buf[7] = data & 0xFF;

	return SpbWriteDataSynchronously(&pDevice->I2CContext, buf, sizeof(buf));
}

NTSTATUS cs35l41_reg_bulk_write(PCS35L41_CONTEXT pDevice, uint32_t reg, uint8_t* data, uint32_t length)
{
	uint8_t buf[4];

	buf[0] = (reg >> 24) & 0xFF;
	buf[1] = (reg >> 16) & 0xFF;
	buf[2] = (reg >> 8) & 0xFF;
	buf[3] = reg & 0xFF;

	return SpbWriteDataSynchronouslyEx(&pDevice->I2CContext, buf, sizeof(buf), data, length);
}

NTSTATUS cs35l41_reg_read(
	_In_ PCS35L41_CONTEXT pDevice,
	uint32_t reg,
	uint32_t* data
) {
	NTSTATUS status;
	uint8_t buf[4];

	buf[0] = (reg >> 24) & 0xFF;
	buf[1] = (reg >> 16) & 0xFF;
	buf[2] = (reg >> 8) & 0xFF;
	buf[3] = reg & 0xFF;

	uint32_t raw_data = 0;
	status = SpbWriteRead(&pDevice->I2CContext, &buf, sizeof(uint32_t), &raw_data, sizeof(uint32_t), 0);
	*data = RtlUlongByteSwap(raw_data);

	return status;
}

NTSTATUS cs35l41_reg_bulk_read(
	_In_ PCS35L41_CONTEXT pDevice,
	uint32_t reg,
	uint32_t* data,
	uint32_t length
) {
	NTSTATUS status = STATUS_IO_DEVICE_ERROR;
	uint8_t buf[4];
	uint32_t raw_data;

	for (int i = 0; i < length; i++) {
		buf[0] = (reg >> 24) & 0xFF;
		buf[1] = (reg >> 16) & 0xFF;
		buf[2] = (reg >> 8) & 0xFF;
		buf[3] = reg & 0xFF;

		status = SpbWriteRead(&pDevice->I2CContext, &buf, sizeof(uint32_t), &raw_data, sizeof(uint32_t), 0);
		data[i] = RtlUlongByteSwap(raw_data);

		reg = reg + 4;
	}

	return status;
}

NTSTATUS cs35l41_reg_update_bits(PCS35L41_CONTEXT pDevice, uint32_t reg, uint32_t mask, uint32_t val)
{
	NTSTATUS status;
	uint32_t temp_val, data;

	status = cs35l41_reg_read(pDevice, reg, &data);

	if (!NT_SUCCESS(status)) {
		return status;
	}

	temp_val = data & ~mask;
	temp_val |= val & mask;

	if (data == temp_val)
	{
		status = STATUS_SUCCESS;
		return status;
	}
	status = cs35l41_reg_write(pDevice, reg, temp_val);

	return status;
}

static const struct cs35l41_otp_map_element_t* cs35l41_find_otp_map(unsigned int otp_id)
{
	int i;

	for (i = 0; i < ARRAYSIZE(cs35l41_otp_map_map); i++) {
		if (cs35l41_otp_map_map[i].id == otp_id)
			return &cs35l41_otp_map_map[i];
	}

	return NULL;
}

NTSTATUS cs35l41_otp_unpack(PCS35L41_CONTEXT pDevice)
{
	const struct cs35l41_otp_map_element_t* otp_map_match;
	const struct cs35l41_otp_packed_element_t* otp_map;
	int bit_offset, word_offset, ret, i;
	unsigned int bit_sum = 8;
	unsigned int otp_val, otp_id_reg;
	unsigned int* otp_mem;

	otp_mem = ExAllocatePool2(
		POOL_FLAG_NON_PAGED,
		sizeof(*otp_mem) * CS35L41_OTP_SIZE_WORDS,
		CS35L41_POOL_TAG
	);
	if (!otp_mem)
		return STATUS_NO_MEMORY;

	ret = cs35l41_reg_read(pDevice, CS35L41_OTPID, &otp_id_reg);
	if (ret) {
		Cs35l41Print(DEBUG_LEVEL_ERROR, DBG_INIT,
			"Read OTP ID failed: %d\n", ret);
		goto exit;
	}

	otp_map_match = cs35l41_find_otp_map(otp_id_reg);

	if (!otp_map_match) {
		Cs35l41Print(DEBUG_LEVEL_ERROR, DBG_INIT,
			"OTP Map matching ID %d not found\n", otp_id_reg);
		ret = STATUS_INVALID_PARAMETER;
		goto exit;
	}

	ret = cs35l41_reg_bulk_read(pDevice, CS35L41_OTP_MEM0, otp_mem, CS35L41_OTP_SIZE_WORDS);
	if (ret) {
		Cs35l41Print(DEBUG_LEVEL_ERROR, DBG_INIT,
			"Read OTP Mem failed: %d\n", ret);
		goto exit;
	}

	otp_map = otp_map_match->map;

	bit_offset = otp_map_match->bit_offset;
	word_offset = otp_map_match->word_offset;

	for (i = 0; i < otp_map_match->num_elements; i++) {
		Cs35l41Print(DEBUG_LEVEL_INFO, DBG_INIT,
			"bitoffset= %d, word_offset=%d, bit_sum mod 32=%d, otp_map[i].size = %u\n",
			bit_offset, word_offset, bit_sum % 32, otp_map[i].size);
		if (bit_offset + otp_map[i].size - 1 >= 32) {
			otp_val = (otp_mem[word_offset] &
				GENMASK(31, bit_offset)) >> bit_offset;
			otp_val |= (otp_mem[++word_offset] &
				GENMASK(bit_offset + otp_map[i].size - 33, 0)) <<
				(32 - bit_offset);
			bit_offset += otp_map[i].size - 32;
		}
		else if (bit_offset + otp_map[i].size - 1 >= 0) {
			otp_val = (otp_mem[word_offset] &
				GENMASK(bit_offset + otp_map[i].size - 1, bit_offset)
				) >> bit_offset;
			bit_offset += otp_map[i].size;
		}
		else /* both bit_offset and otp_map[i].size are 0 */
			otp_val = 0;

		bit_sum += otp_map[i].size;

		if (bit_offset == 32) {
			bit_offset = 0;
			word_offset++;
		}

		if (otp_map[i].reg != 0) {
			ret = cs35l41_reg_update_bits(pDevice, otp_map[i].reg,
				GENMASK(otp_map[i].shift + otp_map[i].size - 1,
					otp_map[i].shift),
				otp_val << otp_map[i].shift);
			if (ret < 0) {
				Cs35l41Print(DEBUG_LEVEL_ERROR, DBG_INIT,
					"Write OTP val failed: %d\n", ret);
				goto exit;
			}
		}
	}

	ret = STATUS_SUCCESS;

exit:
	ExFreePoolWithTag((PVOID)otp_mem, CS35L41_POOL_TAG);

	return ret;
}

static const unsigned char cs35l41_bst_k1_table[4][5] = {
	{ 0x24, 0x32, 0x32, 0x4F, 0x57 },
	{ 0x24, 0x32, 0x32, 0x4F, 0x57 },
	{ 0x40, 0x32, 0x32, 0x4F, 0x57 },
	{ 0x40, 0x32, 0x32, 0x4F, 0x57 }
};

static const unsigned char cs35l41_bst_k2_table[4][5] = {
	{ 0x24, 0x49, 0x66, 0xA3, 0xEA },
	{ 0x24, 0x49, 0x66, 0xA3, 0xEA },
	{ 0x48, 0x49, 0x66, 0xA3, 0xEA },
	{ 0x48, 0x49, 0x66, 0xA3, 0xEA }
};

static const unsigned char cs35l41_bst_slope_table[4] = {
	0x75, 0x6B, 0x3B, 0x28
};

static NTSTATUS cs35l41_boost_config(PCS35L41_CONTEXT pDevice, int boost_ind,
	int boost_cap, int boost_ipk)
{
	unsigned char bst_lbst_val, bst_cbst_range, bst_ipk_scaled;
	int ret;

	switch (boost_ind) {
	case 1000:	/* 1.0 uH */
		bst_lbst_val = 0;
		break;
	case 1200:	/* 1.2 uH */
		bst_lbst_val = 1;
		break;
	case 1500:	/* 1.5 uH */
		bst_lbst_val = 2;
		break;
	case 2200:	/* 2.2 uH */
		bst_lbst_val = 3;
		break;
	default:
		Cs35l41Print(DEBUG_LEVEL_ERROR, DBG_INIT,
			"Invalid boost inductor value: %d nH\n", boost_ind);
		return STATUS_INVALID_PARAMETER;
	}

	if (boost_cap >= 0 && boost_cap <= 19) {
		bst_cbst_range = 0;
	}
	else if (boost_cap >= 20 && boost_cap <= 50) {
		bst_cbst_range = 1;
	}
	else if (boost_cap >= 51 && boost_cap <= 100) {
		bst_cbst_range = 2;
	}
	else if (boost_cap >= 101 && boost_cap <= 200) {
		bst_cbst_range = 3;
	}
	else {
		if (boost_cap < 0) {
			Cs35l41Print(DEBUG_LEVEL_ERROR, DBG_INIT,
				"Invalid boost capacitor value: %d nH\n", boost_cap);
			return STATUS_INVALID_PARAMETER;
		}
		/* 201 uF and greater */
		bst_cbst_range = 4;
	}

	if (boost_ipk < 1600 || boost_ipk > 4500) {
		Cs35l41Print(DEBUG_LEVEL_ERROR, DBG_INIT,
			"Invalid boost inductor peak current: %d mA\n", boost_ipk);
		return STATUS_INVALID_PARAMETER;
	}

	ret = cs35l41_reg_update_bits(pDevice, CS35L41_BSTCVRT_COEFF,
		CS35L41_BST_K1_MASK | CS35L41_BST_K2_MASK,
		cs35l41_bst_k1_table[bst_lbst_val][bst_cbst_range]
		<< CS35L41_BST_K1_SHIFT |
		cs35l41_bst_k2_table[bst_lbst_val][bst_cbst_range]
		<< CS35L41_BST_K2_SHIFT);
	if (ret) {
		Cs35l41Print(DEBUG_LEVEL_ERROR, DBG_INIT,
			"Failed to write boost coefficients: %d\n", ret);
		return ret;
	}

	ret = cs35l41_reg_update_bits(pDevice, CS35L41_BSTCVRT_SLOPE_LBST,
		CS35L41_BST_SLOPE_MASK | CS35L41_BST_LBST_VAL_MASK,
		cs35l41_bst_slope_table[bst_lbst_val]
		<< CS35L41_BST_SLOPE_SHIFT |
		bst_lbst_val << CS35L41_BST_LBST_VAL_SHIFT);
	if (ret) {
		Cs35l41Print(DEBUG_LEVEL_ERROR, DBG_INIT,
			"Failed to write boost slope/inductor value: %d\n", ret);
		return ret;
	}

	bst_ipk_scaled = ((boost_ipk - 1600) / 50) + 0x10;

	ret = cs35l41_reg_update_bits(pDevice, CS35L41_BSTCVRT_PEAK_CUR, CS35L41_BST_IPK_MASK,
		bst_ipk_scaled << CS35L41_BST_IPK_SHIFT);
	if (ret) {
		Cs35l41Print(DEBUG_LEVEL_ERROR, DBG_INIT,
			"Failed to write boost inductor peak current: %d\n", ret);
		return ret;
	}

	cs35l41_reg_update_bits(pDevice, CS35L41_PWR_CTRL2, CS35L41_BST_EN_MASK,
		CS35L41_BST_EN_DEFAULT << CS35L41_BST_EN_SHIFT);

	return 0;
}

void udelay(ULONG usec) {
	LARGE_INTEGER Interval;
	Interval.QuadPart = -10 * (LONGLONG)usec;
	KeDelayExecutionThread(KernelMode, false, &Interval);
}

void msleep(ULONG msec) {
	udelay(msec * 1000);
}

static bool cs35l41_check_cspl_mbox_sts(enum cs35l41_cspl_mbox_cmd cmd,
	enum cs35l41_cspl_mbox_status sts)
{
	switch (cmd) {
	case CSPL_MBOX_CMD_NONE:
	case CSPL_MBOX_CMD_UNKNOWN_CMD:
		return true;
	case CSPL_MBOX_CMD_PAUSE:
	case CSPL_MBOX_CMD_OUT_OF_HIBERNATE:
		return (sts == CSPL_MBOX_STS_PAUSED);
	case CSPL_MBOX_CMD_RESUME:
		return (sts == CSPL_MBOX_STS_RUNNING);
	case CSPL_MBOX_CMD_REINIT:
		return (sts == CSPL_MBOX_STS_RUNNING);
	case CSPL_MBOX_CMD_STOP_PRE_REINIT:
		return (sts == CSPL_MBOX_STS_RDY_FOR_REINIT);
	default:
		return false;
	}
}

NTSTATUS cs35l41_set_cspl_mbox_cmd(PCS35L41_CONTEXT pDevice, enum cs35l41_cspl_mbox_cmd cmd)
{
	unsigned int sts = 0, i;
	int ret;

	// Set mailbox cmd
	ret = cs35l41_reg_write(pDevice, CS35L41_DSP_VIRT1_MBOX_1, cmd);
	if (ret < 0) {
		if (cmd != CSPL_MBOX_CMD_OUT_OF_HIBERNATE) {
			Cs35l41Print(DEBUG_LEVEL_ERROR, DBG_INIT, "Failed to write MBOX: %d\n", ret);
		}
		return ret;
	}

	// Read mailbox status and verify it is appropriate for the given cmd
	for (i = 0; i < 5; i++) {
		udelay(1000);

		ret = cs35l41_reg_read(pDevice, CS35L41_DSP_MBOX_2, &sts);
		if (ret < 0) {
			Cs35l41Print(DEBUG_LEVEL_ERROR, DBG_INIT, "Failed to read MBOX STS: %d\n", ret);
			continue;
		}

		if (!cs35l41_check_cspl_mbox_sts(cmd, sts)) {
			Cs35l41Print(DEBUG_LEVEL_VERBOSE, DBG_INIT, "[%u] cmd %u returned invalid sts %u", i, cmd, sts);
		}
		else
			return 0;
	}

	if (cmd != CSPL_MBOX_CMD_OUT_OF_HIBERNATE)
		Cs35l41Print(DEBUG_LEVEL_ERROR, DBG_INIT, "Failed to set mailbox cmd %u (status %u)\n", cmd, sts);

	return STATUS_INVALID_PARAMETER;
}

static NTSTATUS cs35l41_dsp_init(PCS35L41_CONTEXT pDevice)
{
	int ret;

	cs35l41_reg_write(pDevice, CS35L41_DSP1_RX1_RATE, 0x00000001);
	cs35l41_reg_write(pDevice, CS35L41_DSP1_RX2_RATE, 0x00000001);
	cs35l41_reg_write(pDevice, CS35L41_DSP1_RX3_RATE, 0x00000001);
	cs35l41_reg_write(pDevice, CS35L41_DSP1_RX4_RATE, 0x00000001);
	cs35l41_reg_write(pDevice, CS35L41_DSP1_RX5_RATE, 0x00000001);
	cs35l41_reg_write(pDevice, CS35L41_DSP1_RX6_RATE, 0x00000001);
	cs35l41_reg_write(pDevice, CS35L41_DSP1_RX7_RATE, 0x00000001);
	cs35l41_reg_write(pDevice, CS35L41_DSP1_RX8_RATE, 0x00000001);
	cs35l41_reg_write(pDevice, CS35L41_DSP1_TX1_RATE, 0x00000001);
	cs35l41_reg_write(pDevice, CS35L41_DSP1_TX2_RATE, 0x00000001);
	cs35l41_reg_write(pDevice, CS35L41_DSP1_TX3_RATE, 0x00000001);
	cs35l41_reg_write(pDevice, CS35L41_DSP1_TX4_RATE, 0x00000001);
	cs35l41_reg_write(pDevice, CS35L41_DSP1_TX5_RATE, 0x00000001);
	cs35l41_reg_write(pDevice, CS35L41_DSP1_TX6_RATE, 0x00000001);
	cs35l41_reg_write(pDevice, CS35L41_DSP1_TX7_RATE, 0x00000001);
	cs35l41_reg_write(pDevice, CS35L41_DSP1_TX8_RATE, 0x00000001);

	ret = cs_dsp_load(pDevice);
	if (ret) {
		Cs35l41Print(DEBUG_LEVEL_ERROR, DBG_INIT,
			"DSP Firmware load failed: %X\n", ret);
		return ret;
	}

	cs35l41_reg_write(pDevice, CS35L41_DSP1_RX5_SRC, CS35L41_INPUT_SRC_VPMON);
	cs35l41_reg_write(pDevice, CS35L41_DSP1_RX6_SRC, CS35L41_INPUT_SRC_CLASSH);
	cs35l41_reg_write(pDevice, CS35L41_DSP1_RX7_SRC, CS35L41_INPUT_SRC_TEMPMON);
	cs35l41_reg_write(pDevice, CS35L41_DSP1_RX8_SRC, CS35L41_INPUT_SRC_RSVD);

	//TODO: cs_dsp_coeff_sync_controls

	//HALO DSP Memory lock
	cs35l41_reg_write(pDevice, CS35L41_DSP1_CTRL_BASE + HALO_MPU_LOCK_CONFIG, 0x00005555);
	cs35l41_reg_write(pDevice, CS35L41_DSP1_CTRL_BASE + HALO_MPU_LOCK_CONFIG, 0x0000AAAA);
	cs35l41_reg_write(pDevice, CS35L41_DSP1_CTRL_BASE + HALO_MPU_XMEM_ACCESS_0, 0xFFFFFFFF);
	cs35l41_reg_write(pDevice, CS35L41_DSP1_CTRL_BASE + HALO_MPU_YMEM_ACCESS_0, 0xFFFFFFFF);
	cs35l41_reg_write(pDevice, CS35L41_DSP1_CTRL_BASE + HALO_MPU_WINDOW_ACCESS_0, 0xFFFFFFFF);//lock_regions 
	cs35l41_reg_write(pDevice, CS35L41_DSP1_CTRL_BASE + HALO_MPU_XREG_ACCESS_0, 0xFFFFFFFF);//lock_regions 
	cs35l41_reg_write(pDevice, CS35L41_DSP1_CTRL_BASE + HALO_MPU_YREG_ACCESS_0, 0xFFFFFFFF);//lock_regions 
	cs35l41_reg_write(pDevice, CS35L41_DSP1_CTRL_BASE + HALO_MPU_XMEM_ACCESS_1, 0xFFFFFFFF);
	cs35l41_reg_write(pDevice, CS35L41_DSP1_CTRL_BASE + HALO_MPU_YMEM_ACCESS_1, 0xFFFFFFFF);
	cs35l41_reg_write(pDevice, CS35L41_DSP1_CTRL_BASE + HALO_MPU_WINDOW_ACCESS_1, 0xFFFFFFFF);//lock_regions 
	cs35l41_reg_write(pDevice, CS35L41_DSP1_CTRL_BASE + HALO_MPU_XREG_ACCESS_1, 0xFFFFFFFF);//lock_regions 
	cs35l41_reg_write(pDevice, CS35L41_DSP1_CTRL_BASE + HALO_MPU_YREG_ACCESS_1, 0xFFFFFFFF);//lock_regions 
	cs35l41_reg_write(pDevice, CS35L41_DSP1_CTRL_BASE + HALO_MPU_XMEM_ACCESS_2, 0xFFFFFFFF);
	cs35l41_reg_write(pDevice, CS35L41_DSP1_CTRL_BASE + HALO_MPU_YMEM_ACCESS_2, 0xFFFFFFFF);
	cs35l41_reg_write(pDevice, CS35L41_DSP1_CTRL_BASE + HALO_MPU_WINDOW_ACCESS_2, 0xFFFFFFFF);//lock_regions 
	cs35l41_reg_write(pDevice, CS35L41_DSP1_CTRL_BASE + HALO_MPU_XREG_ACCESS_2, 0xFFFFFFFF);//lock_regions 
	cs35l41_reg_write(pDevice, CS35L41_DSP1_CTRL_BASE + HALO_MPU_YREG_ACCESS_2, 0xFFFFFFFF);//lock_regions 
	cs35l41_reg_write(pDevice, CS35L41_DSP1_CTRL_BASE + HALO_MPU_XMEM_ACCESS_3, 0xFFFFFFFF);
	cs35l41_reg_write(pDevice, CS35L41_DSP1_CTRL_BASE + HALO_MPU_YMEM_ACCESS_3, 0xFFFFFFFF);
	cs35l41_reg_write(pDevice, CS35L41_DSP1_CTRL_BASE + HALO_MPU_WINDOW_ACCESS_3, 0xFFFFFFFF);//lock_regions 
	cs35l41_reg_write(pDevice, CS35L41_DSP1_CTRL_BASE + HALO_MPU_XREG_ACCESS_3, 0xFFFFFFFF);//lock_regions 
	cs35l41_reg_write(pDevice, CS35L41_DSP1_CTRL_BASE + HALO_MPU_YREG_ACCESS_3, 0xFFFFFFFF);//lock_regions 
	cs35l41_reg_write(pDevice, CS35L41_DSP1_CTRL_BASE + HALO_MPU_LOCK_CONFIG, 0x00000000);

	return ret;
}
static NTSTATUS cs35l41_dsp_start(PCS35L41_CONTEXT pDevice)
{
	int ret;

	ret = cs35l41_reg_update_bits(pDevice, CS35L41_DSP1_CTRL_BASE + HALO_CCM_CORE_CONTROL,
		HALO_CORE_RESET | HALO_CORE_EN,
		HALO_CORE_RESET | HALO_CORE_EN);

	if (ret)
		return ret;

	return cs35l41_reg_update_bits(pDevice, CS35L41_DSP1_CTRL_BASE + HALO_CCM_CORE_CONTROL,
		HALO_CORE_RESET, 0);
}

static NTSTATUS cs35l41_dsp_mbox_start(PCS35L41_CONTEXT pDevice)
{
	unsigned int fw_status;

	cs35l41_reg_read(pDevice, CS35L41_DSP_MBOX_2, &fw_status);

	switch (fw_status) {
	case CSPL_MBOX_STS_RUNNING:
	case CSPL_MBOX_STS_PAUSED:
		break;
	default:
		Cs35l41Print(DEBUG_LEVEL_ERROR, DBG_INIT, "Firmware status is invalid: %u\n",
			fw_status);
		return STATUS_INVALID_PARAMETER;
	}

	return cs35l41_set_cspl_mbox_cmd(pDevice, CSPL_MBOX_CMD_RESUME);
	
}

static NTSTATUS cs35l41_amp_enable(PCS35L41_CONTEXT pDevice)
{
	//int ret;

	//pup patch
	cs35l41_reg_write(pDevice, CS35L41_TEST_KEY_CTL, 0x00000055);
	cs35l41_reg_write(pDevice, CS35L41_TEST_KEY_CTL, 0x000000AA);
	cs35l41_reg_write(pDevice, 0x00002084, 0x002F1AA0);
	cs35l41_reg_write(pDevice, CS35L41_TEST_KEY_CTL, 0x000000CC);
	cs35l41_reg_write(pDevice, CS35L41_TEST_KEY_CTL, 0x00000033);

	//global enable safe_to_active
	cs35l41_reg_write(pDevice, CS35L41_TEST_KEY_CTL, 0x00000055);
	cs35l41_reg_write(pDevice, CS35L41_TEST_KEY_CTL, 0x000000AA);
	cs35l41_reg_write(pDevice, 0x0000742C, 0x0000000F);
	cs35l41_reg_write(pDevice, 0x0000742C, 0x00000079);
	cs35l41_reg_update_bits(pDevice, CS35L41_PWR_CTRL1,
		CS35L41_GLOBAL_EN_MASK,
		1 << CS35L41_GLOBAL_EN_SHIFT);
	cs35l41_reg_write(pDevice, CS35L41_PWR_CTRL1, 0x00000001);
	cs35l41_reg_write(pDevice, 0x0000742C, 0x000000F9);
	cs35l41_reg_write(pDevice, 0x00007438, 0x00580941);
	cs35l41_reg_write(pDevice, CS35L41_TEST_KEY_CTL, 0x000000CC);
	cs35l41_reg_write(pDevice, CS35L41_TEST_KEY_CTL, 0x00000033);

	return STATUS_SUCCESS;
}

NTSTATUS
GetDeviceUID(
	_In_ WDFDEVICE FxDevice,
	_In_ PINT32 PUID
)
{
	NTSTATUS status = STATUS_ACPI_NOT_INITIALIZED;
	ACPI_EVAL_INPUT_BUFFER_EX inputBuffer;
	RtlZeroMemory(&inputBuffer, sizeof(inputBuffer));

	inputBuffer.Signature = ACPI_EVAL_INPUT_BUFFER_SIGNATURE_EX;
	status = RtlStringCchPrintfA(
		inputBuffer.MethodName,
		sizeof(inputBuffer.MethodName),
		"_UID"
	);
	if (!NT_SUCCESS(status)) {
		return status;
	}

	WDFMEMORY outputMemory;
	PACPI_EVAL_OUTPUT_BUFFER outputBuffer;
	size_t outputArgumentBufferSize = 32;
	size_t outputBufferSize = FIELD_OFFSET(ACPI_EVAL_OUTPUT_BUFFER, Argument) + outputArgumentBufferSize;

	WDF_OBJECT_ATTRIBUTES attributes;
	WDF_OBJECT_ATTRIBUTES_INIT(&attributes);
	attributes.ParentObject = FxDevice;

	status = WdfMemoryCreate(&attributes,
		NonPagedPoolNx,
		0,
		outputBufferSize,
		&outputMemory,
		(PVOID*)&outputBuffer);
	if (!NT_SUCCESS(status)) {
		return status;
	}

	RtlZeroMemory(outputBuffer, outputBufferSize);

	WDF_MEMORY_DESCRIPTOR inputMemDesc;
	WDF_MEMORY_DESCRIPTOR outputMemDesc;
	WDF_MEMORY_DESCRIPTOR_INIT_BUFFER(&inputMemDesc, &inputBuffer, (ULONG)sizeof(inputBuffer));
	WDF_MEMORY_DESCRIPTOR_INIT_HANDLE(&outputMemDesc, outputMemory, NULL);

	status = WdfIoTargetSendInternalIoctlSynchronously(
		WdfDeviceGetIoTarget(FxDevice),
		NULL,
		IOCTL_ACPI_EVAL_METHOD_EX,
		&inputMemDesc,
		&outputMemDesc,
		NULL,
		NULL
	);
	if (!NT_SUCCESS(status)) {
		goto Exit;
	}

	if (outputBuffer->Signature != ACPI_EVAL_OUTPUT_BUFFER_SIGNATURE) {
		goto Exit;
	}

	if (outputBuffer->Count < 1) {
		goto Exit;
	}

	uint32_t uid;
	if (outputBuffer->Argument[0].DataLength >= 4) {
		uid = *(uint32_t*)outputBuffer->Argument->Data;
	}
	else if (outputBuffer->Argument[0].DataLength >= 2) {
		uid = *(uint16_t*)outputBuffer->Argument->Data;
	}
	else {
		uid = *(uint8_t*)outputBuffer->Argument->Data;
	}
	if (PUID) {
		*PUID = uid;
	}
	else {
		status = STATUS_ACPI_INVALID_ARGUMENT;
	}
Exit:
	if (outputMemory != WDF_NO_HANDLE) {
		WdfObjectDelete(outputMemory);
	}
	return status;
}

BOOLEAN
OnInterruptIsr(
	IN WDFINTERRUPT Interrupt,
	IN ULONG MessageID
)
{
	Cs35l41Print(DEBUG_LEVEL_VERBOSE, DBG_IOCTL,
		"OnInterruptIsr - Entry");



	return TRUE;
}

NTSTATUS
StartCodec(
	PCS35L41_CONTEXT pDevice
) {
	NTSTATUS status = STATUS_SUCCESS;
	if (!pDevice->SetUID) {
		status = STATUS_ACPI_INVALID_DATA;
		return status;
	}

	unsigned int int_status;
	int timeout = 100;
	do {
		if (timeout == 0) {
			Cs35l41Print(DEBUG_LEVEL_ERROR, DBG_PNP,
				"Timeout waiting for OTP_BOOT_DONE\n");
			status = STATUS_DEVICE_BUSY;
			return status;
		}
		udelay(1000);
		status = cs35l41_reg_read(pDevice, CS35L41_IRQ1_STATUS4, &int_status);
		timeout--;
	} while (!(int_status & CS35L41_OTP_BOOT_DONE));

	status = cs35l41_reg_read(pDevice, CS35L41_IRQ1_STATUS3, &int_status);
	if (int_status & CS35L41_OTP_BOOT_ERR) {
		Cs35l41Print(DEBUG_LEVEL_ERROR, DBG_PNP,
			"OTP Boot error\n");
		status = STATUS_INVALID_PARAMETER;
		return status;
	}

	int revid = -1;
	status = cs35l41_reg_read(pDevice, CS35L41_DEVID, &revid);
	if (revid < 0) {
		Cs35l41Print(DEBUG_LEVEL_ERROR, DBG_PNP,
			"Failed to read device ID\n");
		status = STATUS_IO_DEVICE_ERROR;
		return status;
	}

	if (revid != CS35L41_CHIP_ID) {
		Cs35l41Print(DEBUG_LEVEL_ERROR, DBG_PNP,
			"Invalid device id (0x%x), expected 0x%x\n", revid, CS35L41_CHIP_ID);
		status = STATUS_IO_DEVICE_ERROR;
		return status;
	}

	unsigned int reg_revid = 0;
	status = cs35l41_reg_read(pDevice, CS35L41_REVID, &reg_revid);
	if (!NT_SUCCESS(status)) {
		return status;
	}

	Cs35l41Print(DEBUG_LEVEL_INFO, DBG_PNP,
		"CS35L41 revision 0x%02x\n", reg_revid);

	cs35l41_reg_write(pDevice, CS35L41_TEST_KEY_CTL, 0x00000055);
	cs35l41_reg_write(pDevice, CS35L41_TEST_KEY_CTL, 0x000000AA);

	switch (reg_revid) {
	case CS35L41_REVID_B2:
		cs35l41_reg_write(pDevice, CS35L41_VIMON_SPKMON_RESYNC, 0x00000000);
		cs35l41_reg_write(pDevice, 0x00004310, 0x00000000);
		cs35l41_reg_write(pDevice, CS35L41_VPVBST_FS_SEL, 0x00000000);
		cs35l41_reg_write(pDevice, CS35L41_BSTCVRT_DCM_CTRL, 0x00000051);
		cs35l41_reg_write(pDevice, CS35L41_DSP1_YM_ACCEL_PL0_PRI, 0x00000000);
		cs35l41_reg_write(pDevice, CS35L41_DSP1_XM_ACCEL_PL0_PRI, 0x00000000);
		cs35l41_reg_write(pDevice, CS35L41_PWR_CTRL2, 0x00000000);
		cs35l41_reg_write(pDevice, CS35L41_AMP_GAIN_CTRL, 0x00000000);
		cs35l41_reg_write(pDevice, CS35L41_ASP_TX3_SRC, 0x00000000);
		cs35l41_reg_write(pDevice, CS35L41_ASP_TX4_SRC, 0x00000000);
		cs35l41_reg_write(pDevice, CS35L41_TEST_KEY_CTL, 0x0000CCCC);
		cs35l41_reg_write(pDevice, CS35L41_TEST_KEY_CTL, 0x00003333);
		break;
	}

	cs35l41_reg_write(pDevice, CS35L41_DSP1_CCM_CORE_CTRL, 0x00000000);

	unsigned int otp_id_reg;

	cs35l41_otp_unpack(pDevice);

	cs35l41_reg_write(pDevice, CS35L41_TEST_KEY_CTL, 0x000000CC);
	cs35l41_reg_write(pDevice, CS35L41_TEST_KEY_CTL, 0x00000033);

	struct cs35l41_gpio_cfg gpio1;
	struct cs35l41_gpio_cfg gpio2;

	gpio1.pol_inv = false;
	gpio1.out_en = false;
	gpio1.func = 0;
	gpio1.valid = false;

	gpio2.pol_inv = false;
	gpio2.out_en = true;
	//GpioInt in ACPI should be:
	//ActiveLow == func 2 or 4
	//ActiveHigh == func 5
	gpio2.func = 4;
	gpio2.valid = true;

	cs35l41_reg_update_bits(pDevice, CS35L41_GPIO1_CTRL1,
		CS35L41_GPIO_POL_MASK | CS35L41_GPIO_DIR_MASK,
		gpio1.pol_inv << CS35L41_GPIO_POL_SHIFT |
		!gpio1.out_en << CS35L41_GPIO_DIR_SHIFT);

	cs35l41_reg_update_bits(pDevice, CS35L41_GPIO2_CTRL1,
		CS35L41_GPIO_POL_MASK | CS35L41_GPIO_DIR_MASK,
		gpio2.pol_inv << CS35L41_GPIO_POL_SHIFT |
		!gpio2.out_en << CS35L41_GPIO_DIR_SHIFT);

	if (gpio1.valid)
		cs35l41_reg_update_bits(pDevice, CS35L41_GPIO_PAD_CONTROL, CS35L41_GPIO1_CTRL_MASK,
			gpio1.func << CS35L41_GPIO1_CTRL_SHIFT);

	if (gpio2.valid)
		cs35l41_reg_update_bits(pDevice, CS35L41_GPIO_PAD_CONTROL, CS35L41_GPIO2_CTRL_MASK,
			gpio2.func << CS35L41_GPIO2_CTRL_SHIFT);

	cs35l41_reg_write(pDevice, CS35L41_IRQ1_MASK1, CS35L41_INT1_MASK_DEFAULT);

	if (!NT_SUCCESS(status))
	{
		Cs35l41Print(DEBUG_LEVEL_ERROR, DBG_INIT,
			"Error creating WDF interrupt object - 0x%08lX",
			status);

		return status;
	}

	//cirrus,boost-peak-milliamp
	int bst_ipk = 4000;
	//cirrus,boost-ind-nanohenry
	int bst_ind = 1000;
	//cirrus,boost-cap-microfarad
	int bst_cap = 15;

	/* Required */
	cs35l41_boost_config(pDevice, bst_ind, bst_cap, bst_ipk);

	//cirrus,asp-sdout-hiz
	int dout_hiz = 3;
	/* Optional */
	if (dout_hiz <= CS35L41_ASP_DOUT_HIZ_MASK && dout_hiz >= 0)
		cs35l41_reg_update_bits(pDevice, CS35L41_SP_HIZ_CTRL, CS35L41_ASP_DOUT_HIZ_MASK, dout_hiz);

	status = cs35l41_dsp_init(pDevice);
	if (!NT_SUCCESS(status)) {
		return status;
	}

	//DSP1 Preload on
	cs35l41_dsp_start(pDevice);

	//TODO: wm_adsp_buffer_init

	//DSP1 on
	status = cs35l41_dsp_mbox_start(pDevice);
	if (!NT_SUCCESS(status)) {
		return status;
	}

	//Main AMP on
	//cs35l41_amp_enable(pDevice);

	/*
	cs35l41_reg_write(pDevice, CS35L41_PLL_CLK_CTRL, 0x00000430); // 3072000Hz, BCLK Input, PLL_REFCLK_EN = 1
	cs35l41_reg_write(pDevice,  CS35L41_DSP_CLK_CTRL, 0x00000003 ); // DSP CLK EN
	cs35l41_reg_write(pDevice,  CS35L41_GLOBAL_CLK_CTRL, 0x00000003 ); // GLOBAL_FS = 48 kHz
	cs35l41_reg_write(pDevice,  CS35L41_SP_ENABLES, 0x00010000 ); // ASP_RX1_EN = 1
	cs35l41_reg_write(pDevice,  CS35L41_SP_RATE_CTRL, 0x00000021 ); // ASP_BCLK_FREQ = 3.072 MHz
	cs35l41_reg_write(pDevice, CS35L41_SP_FORMAT, 0x10100200); // 16 bits RX/TX slots, I2S, clk consumer
	//cs35l41_reg_write(pDevice,  CS35L41_SP_FORMAT, 0x20200200 ); // 32 bits RX/TX slots, I2S, clk consumer
	//cs35l41_reg_write(pDevice,  CS35L41_SP_HIZ_CTRL, 0x00000002 ); // Hi-Z unused
	cs35l41_reg_write(pDevice,  CS35L41_SP_TX_WL, 0x00000018 ); // 24 cycles/slot
	cs35l41_reg_write(pDevice,  CS35L41_SP_RX_WL, 0x00000018 ); // 24 cycles/slot
	cs35l41_reg_write(pDevice,  CS35L41_DAC_PCM1_SRC, 0x00000008 ); // DACPCM1_SRC = ASPRX1
	cs35l41_reg_write(pDevice,  CS35L41_ASP_TX1_SRC, 0x00000018 ); // ASPTX1 SRC = VMON
	cs35l41_reg_write(pDevice,  CS35L41_ASP_TX2_SRC, 0x00000019 ); // ASPTX2 SRC = IMON
	cs35l41_reg_write(pDevice,  CS35L41_ASP_TX3_SRC, 0x00000032 ); // ASPTX3 SRC = ERRVOL
	cs35l41_reg_write(pDevice,  CS35L41_ASP_TX4_SRC, 0x00000033 ); // ASPTX4 SRC = CLASSH_TGT
	cs35l41_reg_write(pDevice,  CS35L41_DSP1_RX1_SRC, 0x00000008 ); // DSP1RX1 SRC = ASPRX1
	cs35l41_reg_write(pDevice,  CS35L41_DSP1_RX2_SRC, 0x00000009 ); // DSP1RX2 SRC = ASPRX2
	cs35l41_reg_write(pDevice,  CS35L41_DSP1_RX3_SRC, 0x00000018 ); // DSP1RX3 SRC = VMON
	cs35l41_reg_write(pDevice,  CS35L41_DSP1_RX4_SRC, 0x00000019 ); // DSP1RX4 SRC = IMON
	//cs35l41_reg_write(pDevice,  CS35L41_DSP1_RX5_SRC, 0x00000020 ); // DSP1RX5 SRC = ERRVOL
	cs35l41_reg_write(pDevice,  CS35L41_AMP_DIG_VOL_CTRL, 0x00000000 ); // AMP_VOL_PCM  0.0 dB
	cs35l41_reg_write(pDevice,  CS35L41_AMP_GAIN_CTRL, 0x00000084 ); // AMP_GAIN_PCM 4.5 dB
	*/
	
	cs35l41_reg_write(pDevice, CS35L41_PLL_CLK_CTRL, 0x00000430); // 3072000Hz, BCLK Input, PLL_REFCLK_EN = 1
	cs35l41_reg_write(pDevice, CS35L41_DSP_CLK_CTRL, 0x00000003); // DSP CLK EN
	cs35l41_reg_write(pDevice, CS35L41_GLOBAL_CLK_CTRL, 0x00000003); // GLOBAL_FS = 48 kHz
	cs35l41_reg_write(pDevice, CS35L41_SP_ENABLES, 0x00010001); // ASP_RX1_EN = 1, ASP_TX1_EN = 1
	cs35l41_reg_write(pDevice, CS35L41_SP_RATE_CTRL, 0x00000021); // ASP_BCLK_FREQ = 3.072 MHz
	cs35l41_reg_write(pDevice, CS35L41_SP_FORMAT, 0x10100200); // 16 bits RX/TX slots, I2S, clk consumer
	//cs35l41_reg_write(pDevice,  CS35L41_SP_FORMAT, 0x20200200 ); // 32 bits RX/TX slots, I2S, clk consumer
	//cs35l41_reg_write(pDevice,  CS35L41_SP_HIZ_CTRL, 0x00000002 ); // Hi-Z unused/disabled
	cs35l41_reg_write(pDevice, CS35L41_SP_TX_WL, 0x00000010); // 16 cycles/slot
	cs35l41_reg_write(pDevice, CS35L41_SP_RX_WL, 0x00000010); // 16 cycles/slot
	cs35l41_reg_write(pDevice, CS35L41_DAC_PCM1_SRC, 0x00000032); // DACPCM1_SRC = DSP
	cs35l41_reg_write(pDevice, CS35L41_ASP_TX1_SRC, 0x00000032); // ASPTX1 SRC = DSP1RX1
	cs35l41_reg_write(pDevice, CS35L41_ASP_TX2_SRC, 0x00000000); // ASPTX2 SRC = Zero
	cs35l41_reg_write(pDevice, CS35L41_ASP_TX3_SRC, 0x00000000); // ASPTX3 SRC = Zero
	cs35l41_reg_write(pDevice, CS35L41_ASP_TX4_SRC, 0x00000000); // ASPTX4 SRC = Zero
	cs35l41_reg_write(pDevice, CS35L41_DSP1_RX1_SRC, 0x00000008); // DSP1RX1 SRC = ASPRX1
	cs35l41_reg_write(pDevice, CS35L41_DSP1_RX2_SRC, 0x00000009); // DSP1RX2 SRC = ASPRX2
	//cs35l41_reg_write(pDevice, CS35L41_DSP1_RX3_SRC, 0x00000018); // DSP1RX3 SRC = VMON
	//cs35l41_reg_write(pDevice, CS35L41_DSP1_RX4_SRC, 0x00000019); // DSP1RX4 SRC = IMON
	//cs35l41_reg_write(pDevice,  CS35L41_DSP1_RX5_SRC, 0x00000020 ); // DSP1RX5 SRC = ERRVOL
	cs35l41_reg_write(pDevice, CS35L41_AMP_DIG_VOL_CTRL, 0x00000003 ); // AMP_VOL_PCM = 4ms CHECKIT TODO
	cs35l41_reg_write(pDevice, CS35L41_AMP_GAIN_CTRL, 0x00000233 ); // AMP_GAIN_PCM = 17.5dB AMP_GAIN_PDM = 19.5dB

	cs35l41_reg_update_bits(pDevice, CS35L41_PLL_CLK_CTRL,
		CS35L41_PLL_OPENLOOP_MASK,
		1 << CS35L41_PLL_OPENLOOP_SHIFT);
	cs35l41_reg_update_bits(pDevice, CS35L41_PLL_CLK_CTRL,
		CS35L41_REFCLK_FREQ_MASK,
		0x33 << CS35L41_REFCLK_FREQ_SHIFT);
	cs35l41_reg_update_bits(pDevice, CS35L41_PLL_CLK_CTRL,
		CS35L41_PLL_CLK_EN_MASK,
		0 << CS35L41_PLL_CLK_EN_SHIFT);
	cs35l41_reg_update_bits(pDevice, CS35L41_PLL_CLK_CTRL,
		CS35L41_PLL_CLK_SEL_MASK, CS35L41_PLLSRC_SCLK);
	cs35l41_reg_update_bits(pDevice, CS35L41_PLL_CLK_CTRL,
		CS35L41_PLL_OPENLOOP_MASK,
		0 << CS35L41_PLL_OPENLOOP_SHIFT);
	cs35l41_reg_update_bits(pDevice, CS35L41_PLL_CLK_CTRL,
		CS35L41_PLL_CLK_EN_MASK,
		1 << CS35L41_PLL_CLK_EN_SHIFT);

	cs35l41_reg_update_bits(pDevice, CS35L41_SP_RATE_CTRL, 0x3F, 0x33);

	cs35l41_reg_update_bits(pDevice, CS35L41_AMP_DIG_VOL_CTRL,
		CS35L41_AMP_PCM_VOL_MASK,
		0 << CS35L41_AMP_PCM_VOL_SHIFT);

	pDevice->DevicePoweredOn = TRUE;
	return status;
}

NTSTATUS
StopCodec(
	PCS35L41_CONTEXT pDevice
) {
	NTSTATUS status = STATUS_SUCCESS;

	//status = cs35l41_reg_write(pDevice, CS35L41_SFT_RESET, 1);

	if (pDevice->fw_img_info.sym_table)
		ExFreePoolWithTag(pDevice->fw_img_info.sym_table, CS35L41_POOL_TAG);
	if (pDevice->fw_img_info.alg_id_list)
		ExFreePoolWithTag(pDevice->fw_img_info.alg_id_list, CS35L41_POOL_TAG);

	pDevice->DevicePoweredOn = FALSE;
	return status;
}

int CsAudioArg2 = 1;

VOID
CSAudioRegisterEndpoint(
	PCS35L41_CONTEXT pDevice
) {
	CsAudioArg arg;
	RtlZeroMemory(&arg, sizeof(CsAudioArg));
	arg.argSz = sizeof(CsAudioArg);
	arg.endpointType = CSAudioEndpointTypeSpeaker;
	arg.endpointRequest = CSAudioEndpointRegister;
	ExNotifyCallback(pDevice->CSAudioAPICallback, &arg, &CsAudioArg2);
}

VOID
CsAudioCallbackFunction(
	IN PCS35L41_CONTEXT pDevice,
	CsAudioArg* arg,
	PVOID Argument2
) {
	if (!pDevice) {
		return;
	}

	if (Argument2 == &CsAudioArg2) {
		return;
	}

	pDevice->CSAudioManaged = TRUE;

	CsAudioArg localArg;
	RtlZeroMemory(&localArg, sizeof(CsAudioArg));
	RtlCopyMemory(&localArg, arg, min(arg->argSz, sizeof(CsAudioArg)));

	if (localArg.endpointType == CSAudioEndpointTypeDSP && localArg.endpointRequest == CSAudioEndpointRegister) {
		CSAudioRegisterEndpoint(pDevice);
	}
	else if (localArg.endpointType != CSAudioEndpointTypeSpeaker) {
		return;
	}

	if (localArg.endpointRequest == CSAudioEndpointStop) {
		StopCodec(pDevice);
	}
	if (localArg.endpointRequest == CSAudioEndpointStart) {
		StartCodec(pDevice);
	}
}

NTSTATUS
OnPrepareHardware(
	_In_  WDFDEVICE     FxDevice,
	_In_  WDFCMRESLIST  FxResourcesRaw,
	_In_  WDFCMRESLIST  FxResourcesTranslated
)
/*++

Routine Description:

This routine caches the SPB resource connection ID.

Arguments:

FxDevice - a handle to the framework device object
FxResourcesRaw - list of translated hardware resources that
the PnP manager has assigned to the device
FxResourcesTranslated - list of raw hardware resources that
the PnP manager has assigned to the device

Return Value:

Status

--*/
{
	PCS35L41_CONTEXT pDevice = GetDeviceContext(FxDevice);
	BOOLEAN fSpbResourceFound = FALSE;
	NTSTATUS status = STATUS_INSUFFICIENT_RESOURCES;

	UNREFERENCED_PARAMETER(FxResourcesRaw);

	//
	// Parse the peripheral's resources.
	//

	ULONG resourceCount = WdfCmResourceListGetCount(FxResourcesTranslated);

	for (ULONG i = 0; i < resourceCount; i++)
	{
		PCM_PARTIAL_RESOURCE_DESCRIPTOR pDescriptor;
		UCHAR Class;
		UCHAR Type;

		pDescriptor = WdfCmResourceListGetDescriptor(
			FxResourcesTranslated, i);

		switch (pDescriptor->Type)
		{
		case CmResourceTypeConnection:
			//
			// Look for I2C or SPI resource and save connection ID.
			//
			Class = pDescriptor->u.Connection.Class;
			Type = pDescriptor->u.Connection.Type;
			if (Class == CM_RESOURCE_CONNECTION_CLASS_SERIAL &&
				Type == CM_RESOURCE_CONNECTION_TYPE_SERIAL_I2C)
			{
				if (fSpbResourceFound == FALSE)
				{
					status = STATUS_SUCCESS;
					pDevice->I2CContext.I2cResHubId.LowPart = pDescriptor->u.Connection.IdLowPart;
					pDevice->I2CContext.I2cResHubId.HighPart = pDescriptor->u.Connection.IdHighPart;
					fSpbResourceFound = TRUE;
				}
				else
				{
				}
			}
			break;
		default:
			//
			// Ignoring all other resource types.
			//
			break;
		}
	}

	//
	// An SPB resource is required.
	//

	if (fSpbResourceFound == FALSE)
	{
		status = STATUS_NOT_FOUND;
	}

	status = SpbTargetInitialize(FxDevice, &pDevice->I2CContext);

	if (!NT_SUCCESS(status))
	{
		return status;
	}

	status = GetDeviceUID(FxDevice, &pDevice->UID);
	if (!NT_SUCCESS(status)) {
		return status;
	}
	pDevice->SetUID = TRUE;

	return status;
}

NTSTATUS
OnReleaseHardware(
	_In_  WDFDEVICE     FxDevice,
	_In_  WDFCMRESLIST  FxResourcesTranslated
)
/*++

Routine Description:

Arguments:

FxDevice - a handle to the framework device object
FxResourcesTranslated - list of raw hardware resources that
the PnP manager has assigned to the device

Return Value:

Status

--*/
{
	PCS35L41_CONTEXT pDevice = GetDeviceContext(FxDevice);
	NTSTATUS status = STATUS_SUCCESS;

	UNREFERENCED_PARAMETER(FxResourcesTranslated);

	SpbTargetDeinitialize(FxDevice, &pDevice->I2CContext);

	if (pDevice->CSAudioAPICallbackObj) {
		ExUnregisterCallback(pDevice->CSAudioAPICallbackObj);
		pDevice->CSAudioAPICallbackObj = NULL;
	}

	if (pDevice->CSAudioAPICallback) {
		ObfDereferenceObject(pDevice->CSAudioAPICallback);
		pDevice->CSAudioAPICallback = NULL;
	}

	return status;
}

NTSTATUS
OnSelfManagedIoInit(
	_In_
	WDFDEVICE FxDevice
) {
	PCS35L41_CONTEXT pDevice = GetDeviceContext(FxDevice);
	NTSTATUS status = STATUS_SUCCESS;

	// CS Audio Callback

	UNICODE_STRING CSAudioCallbackAPI;
	RtlInitUnicodeString(&CSAudioCallbackAPI, L"\\CallBack\\CsAudioCallbackAPI");


	OBJECT_ATTRIBUTES attributes;
	InitializeObjectAttributes(&attributes,
		&CSAudioCallbackAPI,
		OBJ_KERNEL_HANDLE | OBJ_OPENIF | OBJ_CASE_INSENSITIVE | OBJ_PERMANENT,
		NULL,
		NULL
	);
	status = ExCreateCallback(&pDevice->CSAudioAPICallback, &attributes, TRUE, TRUE);
	if (!NT_SUCCESS(status)) {

		return status;
	}

	pDevice->CSAudioAPICallbackObj = ExRegisterCallback(pDevice->CSAudioAPICallback,
		CsAudioCallbackFunction,
		pDevice
	);
	if (!pDevice->CSAudioAPICallbackObj) {

		return STATUS_NO_CALLBACK_ACTIVE;
	}

	CSAudioRegisterEndpoint(pDevice);

	return status;
}

NTSTATUS
OnD0Entry(
	_In_  WDFDEVICE               FxDevice,
	_In_  WDF_POWER_DEVICE_STATE  FxPreviousState
)
/*++

Routine Description:

This routine allocates objects needed by the driver.

Arguments:

FxDevice - a handle to the framework device object
FxPreviousState - previous power state

Return Value:

Status

--*/
{
	UNREFERENCED_PARAMETER(FxPreviousState);

	PCS35L41_CONTEXT pDevice = GetDeviceContext(FxDevice);
	NTSTATUS status = STATUS_SUCCESS;

	status = StartCodec(pDevice);

	return status;
}

NTSTATUS
OnD0Exit(
	_In_  WDFDEVICE               FxDevice,
	_In_  WDF_POWER_DEVICE_STATE  FxPreviousState
)
/*++

Routine Description:

This routine destroys objects needed by the driver.

Arguments:

FxDevice - a handle to the framework device object
FxPreviousState - previous power state

Return Value:

Status

--*/
{
	UNREFERENCED_PARAMETER(FxPreviousState);

	PCS35L41_CONTEXT pDevice = GetDeviceContext(FxDevice);
	NTSTATUS status = STATUS_SUCCESS;

	status = StopCodec(pDevice);

	return STATUS_SUCCESS;
}

NTSTATUS
Cs35l41EvtDeviceAdd(
	IN WDFDRIVER       Driver,
	IN PWDFDEVICE_INIT DeviceInit
)
{
	NTSTATUS                      status = STATUS_SUCCESS;
	WDF_IO_QUEUE_CONFIG           queueConfig;
	WDF_INTERRUPT_CONFIG          interruptConfig;
	WDF_OBJECT_ATTRIBUTES         attributes;
	WDFDEVICE                     device;
	WDFQUEUE                      queue;
	PCS35L41_CONTEXT               devContext;

	UNREFERENCED_PARAMETER(Driver);

	PAGED_CODE();

	Cs35l41Print(DEBUG_LEVEL_INFO, DBG_PNP,
		"Cs35l41EvtDeviceAdd called\n");

	{
		WDF_PNPPOWER_EVENT_CALLBACKS pnpCallbacks;
		WDF_PNPPOWER_EVENT_CALLBACKS_INIT(&pnpCallbacks);

		pnpCallbacks.EvtDevicePrepareHardware = OnPrepareHardware;
		pnpCallbacks.EvtDeviceReleaseHardware = OnReleaseHardware;
		pnpCallbacks.EvtDeviceSelfManagedIoInit = OnSelfManagedIoInit;
		pnpCallbacks.EvtDeviceD0Entry = OnD0Entry;
		pnpCallbacks.EvtDeviceD0Exit = OnD0Exit;

		WdfDeviceInitSetPnpPowerEventCallbacks(DeviceInit, &pnpCallbacks);
	}

	//
	// Setup the device context
	//

	WDF_OBJECT_ATTRIBUTES_INIT_CONTEXT_TYPE(&attributes, CS35L41_CONTEXT);

	//
	// Create a framework device object.This call will in turn create
	// a WDM device object, attach to the lower stack, and set the
	// appropriate flags and attributes.
	//

	status = WdfDeviceCreate(&DeviceInit, &attributes, &device);

	if (!NT_SUCCESS(status))
	{
		Cs35l41Print(DEBUG_LEVEL_ERROR, DBG_PNP,
			"WdfDeviceCreate failed with status code 0x%x\n", status);

		return status;
	}

	{
		WDF_DEVICE_STATE deviceState;
		WDF_DEVICE_STATE_INIT(&deviceState);

		deviceState.NotDisableable = WdfFalse;
		WdfDeviceSetDeviceState(device, &deviceState);
	}

	WDF_IO_QUEUE_CONFIG_INIT_DEFAULT_QUEUE(&queueConfig, WdfIoQueueDispatchParallel);

	queueConfig.EvtIoInternalDeviceControl = Cs35l41EvtInternalDeviceControl;

	status = WdfIoQueueCreate(device,
		&queueConfig,
		WDF_NO_OBJECT_ATTRIBUTES,
		&queue
	);

	if (!NT_SUCCESS(status))
	{
		Cs35l41Print(DEBUG_LEVEL_ERROR, DBG_PNP,
			"WdfIoQueueCreate failed 0x%x\n", status);

		return status;
	}

	//
	// Create manual I/O queue to take care of hid report read requests
	//

	devContext = GetDeviceContext(device);

	devContext->FxDevice = device;

	WDF_IO_QUEUE_CONFIG_INIT(&queueConfig, WdfIoQueueDispatchManual);

	queueConfig.PowerManaged = WdfFalse;

	status = WdfIoQueueCreate(device,
		&queueConfig,
		WDF_NO_OBJECT_ATTRIBUTES,
		&devContext->ReportQueue
	);

	if (!NT_SUCCESS(status))
	{
		Cs35l41Print(DEBUG_LEVEL_ERROR, DBG_PNP,
			"WdfIoQueueCreate failed 0x%x\n", status);

		return status;
	}

	//
	// Create an interrupt object for hardware notifications
	//
	WDF_INTERRUPT_CONFIG_INIT(
		&interruptConfig,
		OnInterruptIsr,
		NULL);
	interruptConfig.PassiveHandling = TRUE;

	status = WdfInterruptCreate(
		device,
		&interruptConfig,
		WDF_NO_OBJECT_ATTRIBUTES,
		&devContext->InterruptObject);

	return status;
}

VOID
Cs35l41EvtInternalDeviceControl(
	IN WDFQUEUE     Queue,
	IN WDFREQUEST   Request,
	IN size_t       OutputBufferLength,
	IN size_t       InputBufferLength,
	IN ULONG        IoControlCode
)
{
	NTSTATUS            status = STATUS_SUCCESS;
	WDFDEVICE           device;
	PCS35L41_CONTEXT     devContext;

	UNREFERENCED_PARAMETER(OutputBufferLength);
	UNREFERENCED_PARAMETER(InputBufferLength);

	device = WdfIoQueueGetDevice(Queue);
	devContext = GetDeviceContext(device);

	switch (IoControlCode)
	{
	default:
		status = STATUS_NOT_SUPPORTED;
		break;
	}

	WdfRequestComplete(Request, status);

	return;
}