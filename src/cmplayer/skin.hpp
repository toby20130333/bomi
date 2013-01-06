#ifndef SKIN_HPP
#define SKIN_HPP

#include "stdafx.hpp"
#include "global.hpp"

class QWidget;		class QPoint;
class PlayEngine;	class AudioController;
class VideoRenderer;class Mrl;

enum Placeholder : int;

class Skin : public QObject {
	Q_OBJECT
public:
	Skin(QObject *parent = nullptr);
	~Skin();
	bool load(const QString &name, QWidget *parent = nullptr);
	QWidget *widget() const;
	QWidget *screen() const;
	void setVisible(bool visible);
	void connectTo(PlayEngine *engine, AudioController *audio, VideoRenderer *video);
	QString name() const;
	void initializePlaceholders();
	static QStringList dirs();
	static QStringList names(bool reload = false);
	static QString path(const QString &name);
	static QString mediaStateText(State state);
public slots:
	void setMediaNumber(int number);
	void setTotalMediaCount(int count);
signals:
	void windowTitleChanged(const QString &title);
	void windowFilePathChanged(const QString &filePath);
private slots:
	void onDurationChanged(int duration);
	void onTick(int tick);
	void seek(int time);
	void onSeekableChanged(bool seekable);
	void onVolumeChanged(int volume);
	void setVolume(int volume);
	void onActionChanged();
	void onMrlChanged(const Mrl &mrl);
	void onStateChanged(State state);
private:
	bool eventFilter(QObject *o, QEvent *e);
	void checkChildren(QWidget *p);
	bool checkButton(QObject *obj);
	bool checkLabel(QObject *obj);
	bool checkVolumeSlider(QObject *obj);
	bool checkSeekSlider(QObject *obj);
	void setPlaceholder(Placeholder ph, const QString &text);
	static QWidget *topParentWidget(QWidget *widget);
	struct Data;
	Data *d;
};

#endif // SKIN_HPP