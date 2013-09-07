/* Copyright (c) 2013, The Linux Foundation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *  * Neither the name of The Linux Foundation nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <debug.h>
#include <err.h>
#include <smem.h>
#include <msm_panel.h>
#include <board.h>
#include <mipi_dsi.h>
#include <pm8x41.h>

#include "include/panel.h"
#include "panel_display.h"

/*---------------------------------------------------------------------------*/
/* GCDB Panel Database                                                       */
/*---------------------------------------------------------------------------*/
#include "include/panel_toshiba_720p_video.h"
#include "include/panel_nt35590_720p_video.h"
#include "include/panel_nt35590_720p_cmd.h"
#include "include/panel_hx8394a_720p_video.h"
#include "include/panel_nt35596_1080p_video.h"
#include "include/panel_nt35521_720p_video.h"

/*---------------------------------------------------------------------------*/
/* static panel selection variable                                           */
/*---------------------------------------------------------------------------*/
enum {
TOSHIBA_720P_VIDEO_PANEL,
NT35590_720P_CMD_PANEL,
NT35590_720P_VIDEO_PANEL,
NT35596_1080P_VIDEO_PANEL,
HX8394A_720P_VIDEO_PANEL,
NT35521_720P_VIDEO_PANEL
};

static uint32_t panel_id;

int oem_panel_rotation()
{
	int ret = NO_ERROR;
	switch (panel_id) {
	case TOSHIBA_720P_VIDEO_PANEL:
		ret = mipi_dsi_cmds_tx(toshiba_720p_video_rotation,
				TOSHIBA_720P_VIDEO_ROTATION);
		break;
	case NT35590_720P_CMD_PANEL:
		ret = mipi_dsi_cmds_tx(nt35590_720p_cmd_rotation,
				NT35590_720P_CMD_ROTATION);
		break;
	case NT35590_720P_VIDEO_PANEL:
		ret = mipi_dsi_cmds_tx(nt35590_720p_video_rotation,
				NT35590_720P_VIDEO_ROTATION);
		break;
	}

	return ret;
}


int oem_panel_on()
{
	/* OEM can keep there panel spefic on instructions in this
	function */
	return NO_ERROR;
}

int oem_panel_off()
{
	/* OEM can keep there panel spefic off instructions in this
	function */
	return NO_ERROR;
}

static void init_panel_data(struct panel_struct *panelstruct,
			struct msm_panel_info *pinfo,
			struct mdss_dsi_phy_ctrl *phy_db)
{
	switch (panel_id) {
	case TOSHIBA_720P_VIDEO_PANEL:
		panelstruct->paneldata    = &toshiba_720p_video_panel_data;
		panelstruct->panelres     = &toshiba_720p_video_panel_res;
		panelstruct->color        = &toshiba_720p_video_color;
		panelstruct->videopanel   = &toshiba_720p_video_video_panel;
		panelstruct->commandpanel = &toshiba_720p_video_command_panel;
		panelstruct->state        = &toshiba_720p_video_state;
		panelstruct->laneconfig   = &toshiba_720p_video_lane_config;
		panelstruct->paneltiminginfo
					 = &toshiba_720p_video_timing_info;
		panelstruct->backlightinfo = &toshiba_720p_video_backlight;
		pinfo->mipi.panel_cmds
					= toshiba_720p_video_on_command;
		pinfo->mipi.num_of_panel_cmds
					= TOSHIBA_720P_VIDEO_ON_COMMAND;
		memcpy(phy_db->timing,
			toshiba_720p_video_timings, TIMING_SIZE);
		break;
	case NT35590_720P_VIDEO_PANEL:
		panelstruct->paneldata    = &nt35590_720p_video_panel_data;
		panelstruct->panelres     = &nt35590_720p_video_panel_res;
		panelstruct->color        = &nt35590_720p_video_color;
		panelstruct->videopanel   = &nt35590_720p_video_video_panel;
		panelstruct->commandpanel = &nt35590_720p_video_command_panel;
		panelstruct->state        = &nt35590_720p_video_state;
		panelstruct->laneconfig   = &nt35590_720p_video_lane_config;
		panelstruct->paneltiminginfo
					 = &nt35590_720p_video_timing_info;
		panelstruct->backlightinfo = &nt35590_720p_video_backlight;
		pinfo->mipi.panel_cmds
					= nt35590_720p_video_on_command;
		pinfo->mipi.num_of_panel_cmds
					= NT35590_720P_VIDEO_ON_COMMAND;
		memcpy(phy_db->timing,
				nt35590_720p_video_timings, TIMING_SIZE);
		break;
	case NT35521_720P_VIDEO_PANEL:
		panelstruct->paneldata    = &nt35521_720p_video_panel_data;
		panelstruct->panelres     = &nt35521_720p_video_panel_res;
		panelstruct->color        = &nt35521_720p_video_color;
		panelstruct->videopanel   = &nt35521_720p_video_video_panel;
		panelstruct->commandpanel = &nt35521_720p_video_command_panel;
		panelstruct->state        = &nt35521_720p_video_state;
		panelstruct->laneconfig   = &nt35521_720p_video_lane_config;
		panelstruct->paneltiminginfo
					 = &nt35521_720p_video_timing_info;
		panelstruct->backlightinfo = &nt35521_720p_video_backlight;
		pinfo->mipi.panel_cmds
					= nt35521_720p_video_on_command;
		pinfo->mipi.num_of_panel_cmds
					= NT35521_720P_VIDEO_ON_COMMAND;
		memcpy(phy_db->timing,
				nt35521_720p_video_timings, TIMING_SIZE);
		break;
	case HX8394A_720P_VIDEO_PANEL:
		panelstruct->paneldata    = &hx8394a_720p_video_panel_data;
		panelstruct->panelres     = &hx8394a_720p_video_panel_res;
		panelstruct->color        = &hx8394a_720p_video_color;
		panelstruct->videopanel   = &hx8394a_720p_video_video_panel;
		panelstruct->commandpanel = &hx8394a_720p_video_command_panel;
		panelstruct->state        = &hx8394a_720p_video_state;
		panelstruct->laneconfig   = &hx8394a_720p_video_lane_config;
		panelstruct->paneltiminginfo
					 = &hx8394a_720p_video_timing_info;
		panelstruct->backlightinfo = &hx8394a_720p_video_backlight;
		pinfo->mipi.panel_cmds
					= hx8394a_720p_video_on_command;
		pinfo->mipi.num_of_panel_cmds
					= HX8394A_720P_VIDEO_ON_COMMAND;
		memcpy(phy_db->timing,
				hx8394a_720p_video_timings, TIMING_SIZE);
		break;

	case NT35590_720P_CMD_PANEL:
		panelstruct->paneldata    = &nt35590_720p_cmd_panel_data;
		panelstruct->panelres     = &nt35590_720p_cmd_panel_res;
		panelstruct->color        = &nt35590_720p_cmd_color;
		panelstruct->videopanel   = &nt35590_720p_cmd_video_panel;
		panelstruct->commandpanel = &nt35590_720p_cmd_command_panel;
		panelstruct->state        = &nt35590_720p_cmd_state;
		panelstruct->laneconfig   = &nt35590_720p_cmd_lane_config;
		panelstruct->paneltiminginfo = &nt35590_720p_cmd_timing_info;
		panelstruct->backlightinfo = &nt35590_720p_cmd_backlight;
		pinfo->mipi.panel_cmds
					= nt35590_720p_cmd_on_command;
		pinfo->mipi.num_of_panel_cmds
					= NT35590_720P_CMD_ON_COMMAND;
		memcpy(phy_db->timing,
				nt35590_720p_cmd_timings, TIMING_SIZE);
		break;
	case NT35596_1080P_VIDEO_PANEL:
		panelstruct->paneldata    = &nt35596_1080p_video_panel_data;
		panelstruct->panelres     = &nt35596_1080p_video_panel_res;
		panelstruct->color        = &nt35596_1080p_video_color;
		panelstruct->videopanel   = &nt35596_1080p_video_video_panel;
		panelstruct->commandpanel = &nt35596_1080p_video_command_panel;
		panelstruct->state        = &nt35596_1080p_video_state;
		panelstruct->laneconfig   = &nt35596_1080p_video_lane_config;
		panelstruct->paneltiminginfo
					= &nt35596_1080p_video_timing_info;
		panelstruct->backlightinfo
					= &nt35596_1080p_video_backlight;
		pinfo->mipi.panel_cmds
					= nt35596_1080p_video_on_command;
		pinfo->mipi.num_of_panel_cmds
					= NT35596_1080P_VIDEO_ON_COMMAND;
		memcpy(phy_db->timing,
				nt35596_1080p_video_timings, TIMING_SIZE);
		break;
	}
}

#define TIANMA	0
#define TRULY 	1

static int skuf_adc_test()
{
	uint32_t vadc_chan;
	uint16_t chan = 39;
	uint16_t mpp_chan = 7; //0~7

	struct pm8x41_ldo ldo_entry = LDO((0x13F00 + 0x100 * 15), 0);
	pm8x41_ldo_set_voltage(&ldo_entry, 2800000);
	pm8x41_ldo_control(&ldo_entry, 1);

	pm8x41_enable_mpp_as_adc(mpp_chan);
	vadc_chan = pm8x41_adc_channel_read(chan);
	dprintf(CRITICAL, "The channel [%u] voltage is :%u\n",chan, vadc_chan);

	if(vadc_chan >= 0 && vadc_chan < 100000) {
		return TIANMA;
	}
	if(vadc_chan >= 450000 && vadc_chan <= 550000) {
		return TRULY;
	}

	pm8x41_ldo_control(&ldo_entry, 0);
}

bool oem_panel_select(struct panel_struct *panelstruct,
			struct msm_panel_info *pinfo,
			struct mdss_dsi_phy_ctrl *phy_db)
{
	uint32_t hw_id = board_hardware_id();
	uint32_t platformid = board_platform_id();
	uint32_t target_id = board_target_id();
	uint32_t nt35590_panel_id = NT35590_720P_VIDEO_PANEL;

#if DISPLAY_TYPE_CMD_MODE
	nt35590_panel_id = NT35590_720P_CMD_PANEL;
#endif

	switch (platformid) {
	case MSM8974:
		switch (hw_id) {
		case HW_PLATFORM_FLUID:
		case HW_PLATFORM_MTP:
		case HW_PLATFORM_SURF:
			panel_id = TOSHIBA_720P_VIDEO_PANEL;
			break;
		default:
			dprintf(CRITICAL, "Display not enabled for %d HW type\n"
						, hw_id);
			return false;
		}
		break;
	case MSM8826:
	case MSM8626:
	case MSM8226:
	case MSM8926:
	case MSM8126:
	case MSM8326:
	case APQ8026:
		switch (hw_id) {
		case HW_PLATFORM_QRD:
			if (board_hardware_subtype() == 2) {
				if (skuf_adc_test()) {
					panel_id = NT35521_720P_VIDEO_PANEL;
				} else {
					panel_id = HX8394A_720P_VIDEO_PANEL;
				}
			} else {
				if (((target_id >> 16) & 0xFF) == 0x1) //EVT
					panel_id = nt35590_panel_id;
				else if (((target_id >> 16) & 0xFF) == 0x2) //DVT
					panel_id = HX8394A_720P_VIDEO_PANEL;
				else {
					dprintf(CRITICAL, "Not supported device, target_id=%x\n"
							, target_id);
					return false;
				}
			}
			break;
		case HW_PLATFORM_MTP:
		case HW_PLATFORM_SURF:
			panel_id = nt35590_panel_id;
			break;
		default:
			dprintf(CRITICAL, "Display not enabled for %d HW type\n"
						, hw_id);
			return false;
		}
		break;
	default:
		dprintf(CRITICAL, "GCDB:Display: Platform id:%d not supported\n"
					, platformid);
		return false;
	}

	init_panel_data(panelstruct, pinfo, phy_db);

	return true;
}
