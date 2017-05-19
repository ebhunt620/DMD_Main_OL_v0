function varargout = dmd_util(varargin)
% DMD_UTIL MATLAB code for dmd_util.fig
%      DMD_UTIL, by itself, creates a new DMD_UTIL or raises the existing
%      singleton*.
%
%      H = DMD_UTIL returns the handle to a new DMD_UTIL or the handle to
%      the existing singleton*.
%
%      DMD_UTIL('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in DMD_UTIL.M with the given input arguments.
%
%      DMD_UTIL('Property','Value',...) creates a new DMD_UTIL or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before dmd_util_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to dmd_util_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help dmd_util

% Last Modified by GUIDE v2.5 31-Oct-2016 10:46:50

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @dmd_util_OpeningFcn, ...
                   'gui_OutputFcn',  @dmd_util_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before dmd_util is made visible.
function dmd_util_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to dmd_util (see VARARGIN)

% Choose default command line output for dmd_util
%handles.output = hObject;
%set(handles.uipanel2,'selectedobject',handles.multi_roi_radiobutton2)
set(handles.single_roi_radiobutton1,'Value',0);
set(handles.multi_roi_radiobutton2,'Value',0);
set(handles.edges_radiobutton3,'Value',0);
set(handles.text4, 'String', 'Load an Image');

hfileID = fopen('homography.txt','r');
h=fscanf(hfileID,'[%f ,%f , %f ; %f , %f , %f ; %f , %f , %f ] ',[3 3])';
fclose(hfileID);

handles.h =h; %add homography to handles structure
% Update handles structure
guidata(hObject, handles);

% UIWAIT makes dmd_util wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = dmd_util_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% Get default command line output from handles structure
%varargout{1} = handles.output;


% --- Executes on button press in load_image_pushbutton1.
function load_image_pushbutton1_Callback(hObject, eventdata, handles)
% hObject    handle to load_image_pushbutton1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
[FileName PathName]=uigetfile({'*.tiff;*.tif;*.bmp;*.jpg'},'Select Camera Image');

FileName = [PathName FileName];

% DMD Specs
dmd_w = 1024;
dmd_h = 768;
handles.dmd_w = dmd_w; % add dmd params to handles structure
handles.dmd_h = dmd_h;
guidata(hObject, handles); % update guidata

imcamera=imread(FileName);
info=imfinfo(FileName);
xRange=info.Width;
yRange=info.Height;

%outputSize = [dmd_h dmd_w];
%im_scale = imresize(imcamera,outputSize);
im_scale = flipud(uint8(imcamera));
%im_scale = rgb2gray(imcamera);
axes(handles.axes1);
imagesc(im_scale), axis image, axis xy, grid on%colormap(gray), colorbar, grid on
title(FileName)


% --- Executes on button press in save_image_pushbutton2.
function save_image_pushbutton2_Callback(hObject, eventdata, handles)
% hObject    handle to save_image_pushbutton2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
h = handles.h;
homography = projective2d(h);
final_contour =handles.update_contour;
final_contour_warp = flipud(final_contour);
%%final_contour_warp = imwarp(final_contour,homography);
imwrite(final_contour_warp,'dmd_image.bmp');


% --- Executes on slider movement.
function threshold_slider1_Callback(hObject, eventdata, handles)
% hObject    handle to threshold_slider1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider


% --- Executes during object creation, after setting all properties.
function threshold_slider1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to threshold_slider1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function intensity_slider2_Callback(hObject, eventdata, handles)
% hObject    handle to intensity_slider2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
if isempty(get(handles.axes2, 'Children'))
   set(handles.text4, 'String', 'Error: Select an Image / ROI');
else
    intensity_value = int32(get(hObject,'Value'));
    new_contour = handles.contour;
    new_contour(new_contour>0)=intensity_value;
    set(handles.text3, 'String', ['Intensity : ' num2str(intensity_value)]);
    imagesc(new_contour,[0 255]), axis image, axis xy, colormap(gray), colorbar, grid off
    handles.update_contour = new_contour;
    % set(hObject,'Value',0);
end
% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider


% --- Executes during object creation, after setting all properties.
function intensity_slider2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to intensity_slider2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
set(hObject, 'min', 0);
set(hObject, 'max', 255);
%set(hObject, 'SliderStep', [1 1]);
set(hObject, 'Value', 100); % Somewhere between max and min.
% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on button press in single_roi_radiobutton1.
function single_roi_radiobutton1_Callback(hObject, eventdata, handles)
% hObject    handle to single_roi_radiobutton1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
if isempty(get(handles.axes1, 'Children'))
   set(handles.text4, 'String', 'Error: Select an Image');
   set(hObject,'Value',0);
else
    set(handles.text4, 'String', 'Select the Region of Interest; Double Click to end selection.');
    [contour,contour_x,contour_y] = roipoly;
    contour_gray = uint8(contour);
    contour_gray(contour_gray>0)=255;
    handles.contour = contour_gray;
    handles.update_contour = contour_gray;
    guidata(hObject, handles);
    axes(handles.axes2);
    imagesc(contour_gray), axis image, axis xy, colormap(gray), colorbar, grid off
    title('DMD Image')
    set(hObject,'Value',0);
end


% Hint: get(hObject,'Value') returns toggle state of single_roi_radiobutton1


% --- Executes on button press in multi_roi_radiobutton2.
function multi_roi_radiobutton2_Callback(hObject, eventdata, handles)
% hObject    handle to multi_roi_radiobutton2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

%Check to see if an image has been loaded.
%If not, instruct user to select an image.
if isempty(get(handles.axes1, 'Children'))
   set(handles.text4, 'String', 'Error: Select an Image');
   set(hObject,'Value',0);
%If image has been loaded, allow the user to select the ROI.
else
    val=double(get(handles.figure1,'CurrentCharacter'));
    while (val~=100)
    val=double(get(handles.figure1,'CurrentCharacter'));
    set(handles.text4, 'String', 'Select the Region of Interest; Double Click to end selection.');
    [contour,contour_x,contour_y] = roipoly;
    contour_gray = uint8(contour);
    contour_gray(contour_gray>0)=255;
    handles.contour = contour_gray;
    handles.update_contour = contour_gray;
    guidata(hObject, handles);
    axes(handles.axes2);
    imagesc(contour_gray), axis image, axis xy, colormap(gray), colorbar, grid off
    title('DMD Image')
    set(hObject,'Value',0);
    end
end
% Hint: get(hObject,'Value') returns toggle state of multi_roi_radiobutton2


% --- Executes on button press in edges_radiobutton3.
function edges_radiobutton3_Callback(hObject, eventdata, handles)
% hObject    handle to edges_radiobutton3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of edges_radiobutton3


% --- Executes on button press in redraw_pushbutton3.
function redraw_pushbutton3_Callback(hObject, eventdata, handles)
% hObject    handle to redraw_pushbutton3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
cla(handles.axes1,'reset');
cla(handles.axes2,'reset');
set(handles.single_roi_radiobutton1,'Value',0);
set(handles.multi_roi_radiobutton2,'Value',0);
set(handles.edges_radiobutton3,'Value',0);
set(handles.text4, 'String', 'Load an Image');
