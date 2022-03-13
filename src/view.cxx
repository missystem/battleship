#include "view.hxx"

// Convenient type aliases:
using Color = ge211::Color;
using Sprite_set = ge211::Sprite_set;

// You can change this or even determine it some other way:
static int const grid_size = 36;

// File in Resources/ to read background music from. (Might not exist.)
// static std::string const bg_music_filename {"bg_music.mp3"};
static std::string const hit_sound_filename {"hit.mp3"};
static std::string const miss_sound_filename {"miss.mp3"};
static std::string const winner_sound_filename {"winner.mp3"};
static std::string const p1_wins_sound_filename {"player1_wins.mp3"};
static std::string const p2_wins_sound_filename {"player2_wins.mp3"};

// Sound_effect::Sound_effect(const std::string& filename, const Mixer& mixer)
// {
//     load(filename, mixer);
// }
//


View::View(Model const& model, ge211::Mixer& mixer)
        : model_(model),
          dark_piece(grid_size / 2.1, Color::medium_red()),
          small_dark_piece(grid_size / 4, Color::black()),
          light_piece(grid_size / 2.1, Color::white()),
          small_light_piece(grid_size / 4, Color::white()),

          gray_sprite({grid_size, grid_size}, {128, 128, 128}),
          red_sprite({grid_size, grid_size}, Color::medium_red()),
          lime_sprite({grid_size-1, grid_size-1}, {3, 57, 82}),

          lime_sprite2({grid_size-1, grid_size-1}, Color::medium_blue()),
          ship_sprite({grid_size-2, grid_size-2}, {64, 64, 64}),
          potential_attack_sprite({grid_size-1, grid_size-1},
                                  Color::medium_green()),
          PC_wins({grid_size-1, grid_size-1},
                                  Color::medium_cyan()),
          human_wins({grid_size-1, grid_size-1},
                                  Color::medium_yellow()),
          black({grid_size-1, grid_size-1},
                {3, 160, 98}),
          transparent({grid_size-1, grid_size-1},
                {0, 0, 0,0}),
          lightgreyfilter({grid_size, grid_size},
                      {128, 128, 128, 128}),
          mixer_(mixer)

        // You may want to add sprite initialization here
{
    if (mixer_.is_enabled()) {
        load_audio_();
    }
}

void View::draw(Sprite_set& set, ge211::Posn<int> physical_pos)
{

    for (auto pos: model_.board()) {
        set.add_sprite(lime_sprite, board_to_screen(pos), 1);
        if(pos.y>=10 && pos.x<10){
            set.add_sprite(black, board_to_screen(pos), 2);
        }
        if(pos.y<10 && pos.x>=10){
            set.add_sprite(black, board_to_screen(pos), 2);
        }
        if(model_.turn()==Player::dark){
            if(pos.x<10){
                set.add_sprite(transparent, board_to_screen(pos), 10);
            }
            if(pos.x >=10){
                set.add_sprite(gray_sprite, board_to_screen(pos), 10);
            }
        }
        if(model_.turn()==Player::light){
            if(pos.x>=10){
                set.add_sprite(transparent, board_to_screen(pos), 10);
            }
            if(pos.x<10){
                set.add_sprite(gray_sprite, board_to_screen(pos), 10);
            }
        }
        if(model_[pos] == Player::dark){
            if(pos.y>=10 and pos.x<10){
                set.add_sprite(ship_sprite, board_to_screen(pos), 3);
            }
            else if(pos.y>=10){
                    set.add_sprite(lime_sprite, board_to_screen(pos), 3);
            }
            else{
                set.add_sprite(light_piece, board_to_screen(pos), 3);
            }
        }
        if(model_[pos] == Player::light){
            if(pos.y<10 and pos.x>=10){
                set.add_sprite(ship_sprite, board_to_screen(pos), 3);
            }
            else if(pos.y<10){
                set.add_sprite(lime_sprite, board_to_screen(pos), 3);
            }
            else{
                set.add_sprite(light_piece, board_to_screen(pos), 3);
            }
        }
        if(model_[pos] == Player::both){

            set.add_sprite(dark_piece, board_to_screen(pos), 4);
            set.add_sprite(ship_sprite, board_to_screen(pos), 3);
        }
        if (model_.winner() == Player::dark)
        {
            set.add_sprite(transparent, board_to_screen(pos), 10);
            if(pos.x>=10){
                set.add_sprite(lightgreyfilter, board_to_screen(pos), 10);
            }

        }
        if (model_.winner() == Player::light)
        {
            set.add_sprite(transparent, board_to_screen(pos), 10);
            if(pos.x<10){
                set.add_sprite(lightgreyfilter, board_to_screen(pos), 10);
            }
        }



    }
    Move const *ppos = model_.find_move(physical_pos);
    if (ppos != nullptr)
    {
        for (auto pos: ppos->second)
        {
            if((pos.x < 10 && pos.y <10) ||(pos.x>=10 && pos.y >=10))
            set.add_sprite(potential_attack_sprite, board_to_screen(pos), 5);
        }
    }
}

View::Dimensions
View::initial_window_dimensions() const
{
    // You can change this if you want:
    return grid_size * model_.board().dimensions();
}

std::string
View::initial_window_title() const
{
    // You can change this if you want:
    return "Battleship";
}

View::Position
View::board_to_screen(Model::Position logical) const
{
    return {logical.x * grid_size, logical.y * grid_size};
}

Model::Position
View::screen_to_board(View::Position physical) const
{
    return {physical.x / grid_size, physical.y / grid_size};
}

void
View::play_hit_effect() const
{
    mixer_.try_play_effect(hit_sound_);
}

void
View::play_miss_effect() const
{
    mixer_.try_play_effect(miss_sound_);
}

void
View::play_winner_effect() const
{
    mixer_.try_play_effect(winner_sound_);
}

void
View::play_p1_wins_effect() const
{
    mixer_.try_play_effect(p1_wins_sound_);
}
void
View::play_p2_wins_effect() const
{
    mixer_.try_play_effect(p2_wins_sound_);
}

void
View::set_animating(bool active)
{

    if (!active) {
        success_handle_ = {};
    }

}

void
View::resume_music_if_ended() const
{
    if (mixer_.get_music_state() == ge211::Mixer::State::paused) {
        mixer_.resume_music();
    }
}

void
View::load_audio_()
{
    hit_sound_.try_load(hit_sound_filename, mixer_);
    miss_sound_.try_load(miss_sound_filename, mixer_);
    p1_wins_sound_.try_load(p1_wins_sound_filename, mixer_);
    p2_wins_sound_.try_load(p2_wins_sound_filename, mixer_);
    winner_sound_.try_load(winner_sound_filename, mixer_);

}