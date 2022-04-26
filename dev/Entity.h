#ifndef ENTITY_H
#define ENTITY_H

class Entity {
protected:
	bool m_isVisible;
public:
	Entity();
	bool getVisible() const;
	void setVisible(bool isVisible);
	void switchVisible();
};

#endif

