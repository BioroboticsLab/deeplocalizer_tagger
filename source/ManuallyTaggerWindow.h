#ifndef MANUELLTAGWINDOW_H
#define MANUELLTAGWINDOW_H

#include <QMainWindow>
#include <QProgressBar>
#include <ui_ManuallyTaggerWindow.h>

#include "ManuallyTagger.h"
#include "WholeImageWidget.h"
#include "TagWidget.h"


namespace deeplocalizer {
namespace tagger {


class ManuallyTagWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ManuallyTagWindow(std::vector<ImageDescPtr> && _image_desc);
    explicit ManuallyTagWindow(std::unique_ptr<ManuallyTagger> tagger);
    ~ManuallyTagWindow();
public slots:
    void next();
    void back();
    void scroll();
    void scrollBack();
    void setImage(ImageDescPtr desc, ImagePtr img);
protected:
    void keyPressEvent(QKeyEvent *event);
    void resizeEvent(QResizeEvent * );
private slots:
    void updateStatusBar();
    void setProgress(double progress);
private:
    enum class State{Tags, Image};
    Ui::ManuallyTaggerWindow *ui;

    QWidget * _tags_container;
    QGridLayout * _grid_layout;
    WholeImageWidget * _whole_image;
    std::vector<TagWidgetPtr> _tag_widgets;
    QProgressBar * _progres_bar;

    QAction * _nextAct;
    QAction * _backAct;
    QAction * _scrollAct;
    QAction * _scrollBackAct;

    std::unique_ptr<ManuallyTagger> _tagger;
    State _state = State::Tags;
    State _next_state = State::Tags;
    ImageDescPtr  _desc;
    ImagePtr  _image;
    std::deque<std::shared_ptr<QPushButton>> _image_names;

    void init();
    void showImage();
    void showTags();
    void arangeTagWidgets();
    void setupConnections();
    void setupActions();
    void setupUi();
    void eraseNegativeTags();
};
}
}
#endif // MANUELLTAGWINDOW_H
