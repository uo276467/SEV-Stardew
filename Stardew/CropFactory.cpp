#include "CropFactory.h"
#include "Pepper.h"
#include "Tomato.h"
#include "Potato.h"
#include "Broccoli.h"
#include "Eggplant.h"

CropFactory::CropFactory() {

}

Crop* CropFactory::createCrop(InvItem* invItem, float x, float y) {
	std::string name = invItem->name;
	if (name == "pepper") {
		Pepper* pepper = new Pepper(x, y);
		return pepper;
	}else if (name == "tomato") {
		Tomato* tomato = new Tomato(x, y);
		return tomato;
	}else if (name == "potato") {
		Potato* potato = new Potato(x, y);
		return potato;
	}else if (name == "broccoli") {
		Broccoli* broccoli = new Broccoli(x, y);
		return broccoli;
	}
	else if (name == "eggplant") {
		Eggplant* eggplant = new Eggplant(x, y);
		return eggplant;
	}
	return nullptr;
}
