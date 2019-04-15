from flask_wtf import FlaskForm
from wtforms import StringField, PasswordField, SubmitField, BooleanField, IntegerField, TextAreaField
from wtforms.validators import DataRequired, Email, NumberRange

#Login form
class LoginForm(FlaskForm):

	email = StringField('Email', validators=[DataRequired(), Email()])

	password = PasswordField('Password', validators=[DataRequired()])

	remember = BooleanField('Remember Me')

	submit = SubmitField('Login')

class UpdateProfileForm(FlaskForm):

	tiredness = IntegerField('Tiredness', validators=[NumberRange(min=1,max=5)])

	stress = IntegerField('Stress', validators=[NumberRange(min=1,max=5)])

	submit = SubmitField('Update')

class NewPostForm(FlaskForm):

	title = StringField('Title', validators=[DataRequired()])

	content = TextAreaField('Content', validators=[DataRequired()])

	submit = SubmitField('Create New Post')