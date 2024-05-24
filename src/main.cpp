#include <iostream>
#include <random>

#include "app.h"

using namespace Flint;

using Pathfinder::Vec2;
using Pathfinder::Vec3;

const uint32_t WINDOW_WIDTH = 1280;
const uint32_t WINDOW_HEIGHT = 720;

class MyNode : public Node {
public:
    std::weak_ptr<Label> label;

    void custom_ready() override {
        auto margin_container = std::make_shared<MarginContainer>();
        margin_container->set_position({0, 0});
        margin_container->set_size({WINDOW_WIDTH, WINDOW_HEIGHT});
        margin_container->set_margin_all(32);
        margin_container->set_anchor_flag(AnchorFlag::FullRect);
        add_child(margin_container);

        auto vbox_container = std::make_shared<VBoxContainer>();
        vbox_container->set_separation(16);
        margin_container->add_child(vbox_container);

        {
            auto label = std::make_shared<Label>();
            label->set_text("Font file path:");
            vbox_container->add_child(label);

            auto hbox_container = std::make_shared<HBoxContainer>();
            vbox_container->add_child(hbox_container);

            auto text_edit = std::make_shared<TextEdit>();
            text_edit->set_text("Select a font file");
            text_edit->container_sizing.expand_h = true;
            text_edit->container_sizing.flag_h = ContainerSizingFlag::Fill;
            hbox_container->add_child(text_edit);

            auto file_dialog = std::make_shared<FileDialog>();
            add_child(file_dialog);

            auto select_button = std::make_shared<Button>();
            select_button->set_text("Open");

            std::weak_ptr file_dialog_weak = file_dialog;
            std::weak_ptr text_edit_weak = text_edit;

            auto callback = [this, file_dialog_weak, text_edit_weak] {
                auto path = file_dialog_weak.lock()->show();
                if (path.has_value()) {
                    text_edit_weak.lock()->set_text(path.value());
                    auto font = std::make_shared<Font>(path.value());
                    this->set_new_font(font);
                }
            };
            select_button->connect_signal("pressed", callback);
            hbox_container->add_child(select_button);
        }

        auto font = std::make_shared<Font>("Arial Unicode MS Font.ttf");

        auto hbox_container = std::make_shared<HBoxContainer>();
        vbox_container->add_child(hbox_container);

        {
            std::string text = "";
            text += "中文\n";
            text += "英语\n";
            text += "日语\n";
            text += "韩语\n";
            text += "泰语\n";
            text += "阿拉伯语\n";
            text += "俄语\n";
            text += "印尼语\n";
            text += "菲律宾语\n";
            text += "德语\n";
            text += "西班牙语\n";

            auto label = std::make_shared<Label>();
            label->set_text_style(TextStyle{
                ColorU::white(),
                ColorU::red(),
                0,
                false,
                false,
                false,
            });
            label->set_text(text);
            hbox_container->add_child(label);

            label->set_font(font);
        }

        {
            std::string text2 = "";
            text2 += "你好世界\n";
            text2 += "hello world\n";
            text2 += "こんにちは世界\n";
            text2 += "안녕 세계\n";
            text2 += "สวัสดีชาวโลก\n";
            text2 += "مرحبا بالعالم\n";
            text2 += "Привет, мир\n";
            text2 += "Halo Dunia\n";
            text2 += "kumusta mundo\n";
            text2 += "Hallo Welt\n";
            text2 += "Hola Mundo";

            auto label2 = std::make_shared<Label>();
            label2->set_text_style(TextStyle{
                ColorU::white(),
                ColorU::red(),
                0,
                false,
                false,
                false,
            });
            label2->set_text(text2);
            label2->container_sizing.expand_h = true;
            label2->container_sizing.flag_h = ContainerSizingFlag::ShrinkEnd;
            hbox_container->add_child(label2);

            label2->set_font(font);

            label = label2;
        }
    }

    void set_new_font(std::shared_ptr<Font> new_font) {
        label.lock()->set_font(new_font);
    }
};

int main() {
    App app({WINDOW_WIDTH, WINDOW_HEIGHT});

    app.get_tree()->replace_root(std::make_shared<MyNode>());

    app.main_loop();

    return EXIT_SUCCESS;
}
