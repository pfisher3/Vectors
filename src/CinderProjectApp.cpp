#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Camera.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class CinderProjectApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    void resize();
    
    Matrix44f mCubeRotation;
    CameraPersp mCam;
    
//    Adding Light direction and position
    Vec3f   mLightDirection;
    ColorAf mColor;
    
};

void CinderProjectApp::setup()
{
    Vec3f eyePoint(200.0f, 300.0f, -400.0f);
    Vec3f target = Vec3f::zero();
    mCam.lookAt(eyePoint, target);
    mCubeRotation.setToIdentity();
    
//    Calling the Light direction
    mLightDirection = Vec3f(100, 100, -400.0f);
}

void CinderProjectApp::mouseDown( MouseEvent event )
{
}
void CinderProjectApp::resize(){
    mCam.setPerspective(60, getWindowAspectRatio(), 1, 1000);
    gl::setMatrices(mCam);
}

void CinderProjectApp::update()
{
    mCubeRotation.rotate(Vec3f( 1, 1, 1), toRadians(0.2f));
}

void CinderProjectApp::draw()
{
    
    gl::enableDepthRead();
    gl::enableDepthWrite();
    
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    
    Vec2i pos = getMousePos();
    mColor = ColorAf(1.0f, lmap<float>(pos.x, 0.0f, (float)getWindowWidth(), 0.0f, 1.0f),  0.0f);
    
    gl::color(ColorAf::white());
    
    glLoadIdentity();
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat lightPosition[] = {
        -mLightDirection.x,
        -mLightDirection.y,
        -mLightDirection.z,
        0
    };
    
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mColor);
    
    gl::setMatrices(mCam);
    
    
    
    Vec3f size(200.0f, 200.0f, 200.0f);
    Vec3f center(getWindowCenter(), 0);
    
//    gl::drawSolidRect(getWindowBounds());
    glPushMatrix();
        gl::multModelView( mCubeRotation);
        gl::drawCube(Vec3f::zero(), size);
    glPopMatrix();
    
  
}

CINDER_APP_NATIVE( CinderProjectApp, RendererGl )
