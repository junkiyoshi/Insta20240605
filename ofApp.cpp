#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofSetLineWidth(2);
	ofEnableDepthTest();

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 100, true, true, true);
	this->word = "GOOD CODE ";
}
//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->noise_step += 0.02;
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(215);
	ofRotateY(180);

	int size = 33;
	for (int base_deg = 0; base_deg < 330; base_deg += 5) {

		ofPushMatrix();
		ofRotateY(base_deg);

		int deg_span = 36;
		int deg_start = (int)ofMap(ofNoise(base_deg * 0.0085 + this->noise_step), 0, 1, -360, 360);
		int word_index = 0;
		for (int deg = deg_start; deg < deg_start + 360; deg += deg_span) {

			ofPath chara_path = this->font.getCharacterAsPoints(this->word[word_index++], true, false);
			vector<ofPolyline> outline = chara_path.getOutline();

			ofPushMatrix();
			ofTranslate(0, 0, -320);
			ofRotateX(deg);

			ofColor fill_color;
			fill_color.setHsb(ofMap((deg - deg_start) / 180, 0, 2, 0, 255), 200, 200);

			ofFill();
			ofSetColor(fill_color);
			ofBeginShape();
			for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

				ofNextContour(true);

				auto vertices = outline[outline_index].getVertices();
				for (auto& vertex : vertices) {

					glm::vec3 location = vertex / 100 * size;
					location -= glm::vec3(size * 0.5, -size * 0.5, 70);

					ofVertex(location);
				}
			}
			ofEndShape(true);

			ofNoFill();
			ofSetColor(39);
			ofBeginShape();
			for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

				ofNextContour(true);

				auto vertices = outline[outline_index].getVertices();
				for (auto& vertex : vertices) {

					glm::vec3 location = vertex / 100 * size;
					location -= glm::vec3(size * 0.5, -size * 0.5, 70);

					ofVertex(location);
				}
			}
			ofEndShape(true);

			ofPopMatrix();


		}

		ofPopMatrix();
	}

	this->cam.end();

	/*
	int start = 680;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}