#ifndef OCTOON_APPLICATION_H_
#define OCTOON_APPLICATION_H_

#include <chrono>
#include <octoon/game_types.h>

namespace octoon
{
	class OCTOON_EXPORT GameApplication
	{
	public:
		GameApplication() noexcept;
		GameApplication(WindHandle hwnd, std::uint32_t w, std::uint32_t h, std::uint32_t framebuffer_w, std::uint32_t framebuffer_h) except;
		virtual ~GameApplication() noexcept;

		void open(WindHandle hwnd, std::uint32_t w, std::uint32_t h, std::uint32_t framebuffer_w, std::uint32_t framebuffer_h) except;
		void close() noexcept;

		void set_active(bool active) except;
		bool get_active() const noexcept;

		void set_game_listener(GameListenerPtr&& listener) noexcept;
		void set_game_listener(const GameListenerPtr& listener) noexcept;
		const GameListenerPtr& get_game_listener() const noexcept;

		bool is_quit_request() const noexcept;

		bool open_scene(const GameScenePtr& scene) except;
		bool open_scene(const std::string& name) except;
		void close_scene(const GameScenePtr& name) noexcept;
		void close_scene(const std::string& name) noexcept;
		GameScenePtr find_scene(const std::string& name) noexcept;

		template<typename T, typename = std::enable_if_t<std::is_base_of<GameFeature, T>::value>>
		void add_feature() except { this->add_feature(std::make_shared<T>()); }
		void add_feature(const GameFeaturePtr& feature) except;
		void add_feature(GameFeaturePtr&& feature) except;
		void remove_feature(const GameFeaturePtr& feature) except;

		void send_input_event(const input::InputEvent& event) except;

		void do_window_resize(WindHandle window, std::uint32_t w, std::uint32_t h) except;
		void do_window_framebuffer_resize(WindHandle window, std::uint32_t w, std::uint32_t h) except;
		void do_window_close(WindHandle window) except;
		void do_window_focus(WindHandle window, bool focus) except;
		void do_window_key_down(WindHandle window, std::uint16_t input_key, std::uint16_t scancode, std::uint16_t mods) except;
		void do_window_key_up(WindHandle window, std::uint16_t input_key, std::uint16_t scancode, std::uint16_t mods) except;
		void do_window_key_press(WindHandle window, std::uint16_t input_key, std::uint16_t scancode, std::uint16_t mods) except;
		void do_window_key_char(WindHandle window, std::uint16_t unicode, std::uint16_t mods) except;
		void do_window_mouse_button_down(WindHandle window, std::uint8_t input_button, float x, float y) except;
		void do_window_mouse_button_up(WindHandle window, std::uint8_t input_button, float x, float y) except;
		void do_window_mouse_button_double_click(WindHandle window, std::uint8_t input_button, float x, float y) except;
		void do_window_mouse_motion(WindHandle window, float x, float y) except;
		void do_window_scrool(WindHandle window, float x, float y) except;
		void do_window_drop(WindHandle window, std::uint32_t count, const char** file_utf8) except;

		void update() except;

	protected:
		virtual void on_message(const std::string& message) noexcept;

	private:
		GameApplication(const GameApplication&) noexcept = delete;
		GameApplication& operator=(const GameApplication&) noexcept = delete;

	private:
		GameServerPtr game_server_;
		GameListenerPtr game_listener_;

		GameFeaturePtr io_feature_;
		GameFeaturePtr timer_feature_;
		GameFeaturePtr input_feature_;
		GameFeaturePtr base_feature_;
		GameFeaturePtr gui_feature_;

		std::chrono::time_point<std::chrono::high_resolution_clock> start_time_;
	};
}

#endif