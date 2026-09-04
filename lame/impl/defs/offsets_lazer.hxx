#pragma once

#include <cstdint>
#include <string>

namespace offsets::lazer {

    inline constexpr const char* anchor_pattern =
        "01 01 00 00 00 00 80 44 00 00 40 44";

    struct table_t {
        std::string osu_version = "2026.804.2";

        uint32_t api_access_game = 0x310;
        uint32_t ext_link_opener_api = 0x218;

        // osu.Game.OsuGameBase (2026.804.2)
        uint32_t game_base_beatmap_clock = 0x4D0;
        uint32_t game_base_beatmap = 0x450;
        uint32_t game_base_api = 0x438;
        uint32_t game_base_selected_mods = 0x460;

        // osu.Game.OsuGame / osu.Framework.Screens.ScreenStack
        uint32_t game_screen_stack = 0x610;
        uint32_t screen_stack_stack = 0x320;
        uint32_t stack_array = 0x08;
        uint32_t stack_size = 0x10;

        // Original LAME beatmap-clock chain. The OsuGameBase beatmapClock field
        // itself is still exactly +0x4D0 on 2026.804.2.
        uint32_t framed_clock_final_source = 0x210;
        uint32_t framed_clock_current_time = 0x30;

        // WorkingBeatmap / BeatmapInfo
        uint32_t working_map_info = 0x08;
        uint32_t working_map_set_info = 0x10;
        uint32_t map_info_online_id = 0x8C;
        uint32_t map_info_hash = 0x50;
        uint32_t map_info_difficulty = 0x18;
        uint32_t map_info_set_info = 0x48;
        uint32_t set_info_online_id = 0x30;

        // PlayerLoader / Player / GameplayState (2026.804.2)
        uint32_t player_loader_current_player = 0x428;
        uint32_t player_api = 0x3F0;
        uint32_t player_game = 0x400;
        uint32_t player_gameplay_state = 0x408;
        uint32_t player_ruleset = 0x410;
        uint32_t player_drawable_ruleset = 0x458;
        uint32_t gameplay_state_beatmap = 0x08;
        uint32_t gameplay_state_ruleset = 0x10;

        // Kept for source compatibility; Player resolution no longer depends on it.
        uint32_t submitting_player_api = 0x4F0;

        // Bindable / collections
        uint32_t bindable_value = 0x20;
        uint32_t bindable_number_value = 0x40;
        uint32_t list_items = 0x08;
        uint32_t list_size = 0x10;
        uint32_t array_first_element = 0x10;

        // DrawableRuleset<OsuHitObject> / OsuBeatmap
        uint32_t drawable_osu_beatmap = 0x380;
        uint32_t beatmap_info = 0x10;
        uint32_t beatmap_hit_objects = 0x28;

        // HitObject / OsuHitObject / Slider
        uint32_t hit_object_start_time_bindable = 0x10;
        uint32_t osu_hit_object_position_xy = 0x58;
        uint32_t hit_object_nested_objects = 0x28;
        uint32_t hit_object_has_duration = 0; // removed: old +0xD0 heuristic is invalid now
        uint32_t slider_path_wrapper = 0xE0;
        // SliderPath.calculatedPath is a List<Vector2> at +0x20. Using this
        // preserves the old reader's expected point format without guessing BindableList internals.
        uint32_t path_ctrl_points_list = 0x20;
        uint32_t slider_repeat_count = 0x130;

        [[nodiscard]] bool has_hitobject_offsets() const {
            return drawable_osu_beatmap != 0 &&
                beatmap_hit_objects != 0 &&
                list_items != 0 &&
                list_size != 0 &&
                hit_object_start_time_bindable != 0 &&
                bindable_value != 0;
        }
    };

    inline bool load_from_file(table_t& out, const std::wstring& path) {
        return true;
    }

    inline std::wstring default_json_path() {
        return L"";
    }

}
